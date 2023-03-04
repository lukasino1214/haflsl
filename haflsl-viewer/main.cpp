#include "haflsl/nodes.hpp"
#include <haflsl/compiler.hpp>
#include <haflsl/lexer.hpp>
#include <haflsl/utils.hpp>

#include <daxa/daxa.hpp>
#include <daxa/utils/pipeline_manager.hpp>
#include <daxa/utils/imgui.hpp>
#include <memory>

using namespace daxa::types;

#include <GLFW/glfw3.h>
#if defined(_WIN32)
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_NATIVE_INCLUDE_NONE
using HWND = void *;
#elif defined(__linux__)
#define GLFW_EXPOSE_NATIVE_X11
#define GLFW_EXPOSE_NATIVE_WAYLAND
#endif
#include <GLFW/glfw3native.h>

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_glfw.h>

#include <thread>

#include "text_editor.hpp"

template <typename App>
struct AppWindow {
    GLFWwindow * glfw_window_ptr;
    u32 size_x = 800, size_y = 600;
    bool minimized = false;

    AppWindow(char const * window_name) {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfw_window_ptr = glfwCreateWindow(static_cast<i32>(size_x), static_cast<i32>(size_y), window_name, nullptr, nullptr);
        glfwSetWindowUserPointer(glfw_window_ptr, this);
        glfwSetCursorPosCallback(
            glfw_window_ptr,
            [](GLFWwindow * window_ptr, f64 x, f64 y)
            {
                auto & app = *reinterpret_cast<App *>(glfwGetWindowUserPointer(window_ptr));
                app.on_mouse_move(static_cast<f32>(x), static_cast<f32>(y));
            });
        glfwSetScrollCallback(
            glfw_window_ptr,
            [](GLFWwindow * window_ptr, f64 x, f64 y)
            {
                auto & app = *reinterpret_cast<App *>(glfwGetWindowUserPointer(window_ptr));
                app.on_mouse_scroll(static_cast<f32>(x), static_cast<f32>(y));
            });
        glfwSetMouseButtonCallback(
            glfw_window_ptr,
            [](GLFWwindow * window_ptr, i32 key, i32 action, i32)
            {
                auto & app = *reinterpret_cast<App *>(glfwGetWindowUserPointer(window_ptr));
                app.on_mouse_button(key, action);
            });
        glfwSetKeyCallback(
            glfw_window_ptr,
            [](GLFWwindow * window_ptr, i32 key, i32, i32 action, i32)
            {
                auto & app = *reinterpret_cast<App *>(glfwGetWindowUserPointer(window_ptr));
                app.on_key(key, action);
            });
        glfwSetWindowSizeCallback(
            glfw_window_ptr,
            [](GLFWwindow * window_ptr, i32 sx, i32 sy)
            {
                auto & app = *reinterpret_cast<App *>(glfwGetWindowUserPointer(window_ptr));
                app.on_resize(static_cast<u32>(sx), static_cast<u32>(sy));
            });
    }

    ~AppWindow() {
        glfwDestroyWindow(glfw_window_ptr);
        glfwTerminate();
    }

    auto get_native_platform() -> daxa::NativeWindowPlatform {
        switch(glfwGetPlatform()) {
            case GLFW_PLATFORM_WIN32: return daxa::NativeWindowPlatform::WIN32_API;
            case GLFW_PLATFORM_X11: return daxa::NativeWindowPlatform::XLIB_API;
            case GLFW_PLATFORM_WAYLAND: return daxa::NativeWindowPlatform::WAYLAND_API;
            default: return daxa::NativeWindowPlatform::UNKNOWN;
        }
    }

    auto get_native_handle(GLFWwindow* glfw_window_ptr) -> daxa::NativeWindowHandle {
        #if defined(_WIN32)
            return glfwGetWin32Window(glfw_window_ptr);
        #elif defined(__linux__)
            switch (get_native_platform()) {
                case daxa::NativeWindowPlatform::WAYLAND_API:
                    return reinterpret_cast<daxa::NativeWindowHandle>(glfwGetWaylandWindow(glfw_window_ptr));
                case daxa::NativeWindowPlatform::XLIB_API:
                default:
                    return reinterpret_cast<daxa::NativeWindowHandle>(glfwGetX11Window(glfw_window_ptr));
            }
        #endif
    }

    void set_mouse_pos(f32 x, f32 y) {
        glfwSetCursorPos(glfw_window_ptr, static_cast<f64>(x), static_cast<f64>(y));
    }

    void set_mouse_capture(bool should_capture) {
        glfwSetCursorPos(glfw_window_ptr, static_cast<f64>(size_x / 2), static_cast<f64>(size_y / 2));
        glfwSetInputMode(glfw_window_ptr, GLFW_CURSOR, should_capture ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
        glfwSetInputMode(glfw_window_ptr, GLFW_RAW_MOUSE_MOTION, should_capture);
    }
};

struct App : AppWindow<App> {
    daxa::Context context = daxa::create_context({
        .enable_validation = true
    });

    daxa::Device device = context.create_device({
        .debug_name = "my gpu"
    });

    daxa::Swapchain swapchain = device.create_swapchain({
        .native_window = get_native_handle(glfw_window_ptr),
        .present_mode = daxa::PresentMode::DO_NOT_WAIT_FOR_VBLANK,
        .image_usage = daxa::ImageUsageFlagBits::TRANSFER_DST,
        .debug_name = "swapchain"
    });

    HAFLSL::Compiler compiler = HAFLSL::create_compiler({
        .show_debug_info = true
    });

    daxa::PipelineManager pipeline_manager = daxa::PipelineManager({
        .device = device,
        .shader_compile_options = {
            .root_paths = {
                "/shaders",
                "../shaders",
                "../../shaders",
                "../../../shaders",
                "shaders",
                DAXA_SHADER_INCLUDE_DIR,
            },
            .language = daxa::ShaderLanguage::GLSL,
            .enable_debug_info = true,
        },
        .debug_name = "pipeline_manager",
    });

    std::filesystem::path file_path = "shader.test";
    std::string source_code = HAFLSL::read_file_to_string(file_path.generic_string());
    std::vector<u32> spirv = compiler.compile(file_path);
    std::string spirv_dissambly = compiler.get_spirv_dissambly(spirv);
    HAFLSL::AST ast = compiler.get_ast(file_path);


    bool is_stmt = false;
    bool is_expr = false;    
    HAFLSL::Statement* selected_stmt = {};
    HAFLSL::Expression* selected_expr = {};

    std::shared_ptr<daxa::RasterPipeline> raster_pipeline = pipeline_manager.add_raster_pipeline({
        .vertex_shader_info = {.source = daxa::ShaderFile{"draw.glsl"}, .compile_options = {.defines = {daxa::ShaderDefine{"DRAW_VERT"}}}},
        .fragment_shader_info = { .source = spirv },
        .color_attachments = {{ .format = swapchain.get_format() }},
        .raster = {
            .face_culling = daxa::FaceCullFlagBits::NONE
        },
        .push_constant_size = 0,
        .debug_name = "raster_pipeline",
    }).value();

    daxa::ImGuiRenderer imgui_renderer = create_imgui_renderer();
    auto create_imgui_renderer() -> daxa::ImGuiRenderer {
        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForVulkan(glfw_window_ptr, true);
        daxa::ImGuiRenderer imgui_renderer =  daxa::ImGuiRenderer({
            .device = device,
            .format = swapchain.get_format(),
        });
        ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        ImGui::GetStyle().Colors[ImGuiCol_WindowBg].w = 0.85f;
        return imgui_renderer;
    }

    TextEditor editor = create_editor();
    auto create_editor() -> TextEditor {
        TextEditor editor;
        auto lang = TextEditor::LanguageDefinition::GLSL();
        editor.SetLanguageDefinition(lang);
        editor.SetText(source_code);
        editor.SetShowWhitespaces(false);

        return editor;
    }

    bool paused = false;

    App() : AppWindow<App>("haflsl-viewer") {}

    ~App() {
        device.wait_idle();
        device.collect_garbage();
    }

    bool update() {
        glfwPollEvents();
        if (glfwWindowShouldClose(glfw_window_ptr)) {
            return true;
        }

        if (!minimized) {
            on_update();
        } else {
            using namespace std::literals;
            std::this_thread::sleep_for(1ms);
        }

        return false;
    }

    void ui_update() {
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
            ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoBackground;
            const ImGuiViewport *viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::Begin("DockSpace Demo", nullptr, window_flags);
            ImGui::PopStyleVar(3);
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);


            if (ImGui::BeginMenuBar()) {
                if (ImGui::BeginMenu("Option")) {
                    if (ImGui::MenuItem("Compile", "")) {
                        source_code = editor.GetText();
                        spirv = compiler.compile(source_code);
                        spirv_dissambly = compiler.get_spirv_dissambly(spirv);
                        ast = compiler.get_ast(source_code);

                        raster_pipeline = pipeline_manager.add_raster_pipeline({
                            .vertex_shader_info = {.source = daxa::ShaderFile{"draw.glsl"}, .compile_options = {.defines = {daxa::ShaderDefine{"DRAW_VERT"}}}},
                            .fragment_shader_info = { .source = spirv },
                            .color_attachments = {{ .format = swapchain.get_format() }},
                            .raster = {
                                .face_culling = daxa::FaceCullFlagBits::NONE
                            },
                            .push_constant_size = 0,
                            .debug_name = "raster_pipeline",
                        }).value();

                        selected_stmt = nullptr;
                        selected_expr = nullptr;
                    }

                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar();
            }

            ImGui::End();
        }

        ImGui::Begin("Text editor");
        auto cpos = editor.GetCursorPosition();
        ImGui::Text("%6d/%-6d %6d lines  | %s | %s | %s | %s", cpos.mLine + 1, cpos.mColumn + 1, editor.GetTotalLines(),
			editor.IsOverwrite() ? "Ovr" : "Ins",
			editor.CanUndo() ? "*" : " ",
			editor.GetLanguageDefinition().mName.c_str(), file_path.c_str());

		editor.Render("TextEditor");
        ImGui::End();

        std::function<void(std::unique_ptr<HAFLSL::Expression>&)> print_expr;
        print_expr = [&](std::unique_ptr<HAFLSL::Expression>& expr) {
            if(ImGui::TreeNode((std::string{expr->get_name().data()} + "##" + std::to_string(expr->uuid)).c_str())) {
                if (ImGui::IsItemClicked()) {
                    is_stmt = false;
                    is_expr = true;
                    selected_stmt = nullptr;
                    selected_expr = expr.get();
                }

                switch(expr->get_type()) {
                    case HAFLSL::ExpressionType::ConstantValueExpression: {
                        break;
                    }
                    case HAFLSL::ExpressionType::BinaryExpression: {
                        auto* e = dynamic_cast<HAFLSL::BinaryExpression*>(expr.get());
                        print_expr(e->left);
                        print_expr(e->right);
                        break;
                    }
                    case HAFLSL::ExpressionType::UnaryExpression: {
                        break;
                    }
                    case HAFLSL::ExpressionType::IdentifierExpression: {
                        break;
                    }
                    case HAFLSL::ExpressionType::AccessIdentifierExpression: {
                        break;
                    }
                    case HAFLSL::ExpressionType::AccessIndexExpression: {
                        break;
                    }
                    case HAFLSL::ExpressionType::AssignExpression: {
                        auto* e = dynamic_cast<HAFLSL::AssignExpression*>(expr.get());
                        print_expr(e->left);
                        print_expr(e->right);
                        break;
                    }
                    case HAFLSL::ExpressionType::CallFunctionExpression: {
                        auto* e = dynamic_cast<HAFLSL::CallFunctionExpression*>(expr.get());
                        print_expr(e->function_expr);
                        break;
                    }
                    case HAFLSL::ExpressionType::ConstructorExpression: {
                        auto* e = dynamic_cast<HAFLSL::ConstructorExpression*>(expr.get());

                        for(auto& node : e->values) {
                            print_expr(node);
                        }

                        break;
                    }
                }

                ImGui::TreePop();
            }
        };

        std::function<void(std::unique_ptr<HAFLSL::Statement>&)> print_stmt;
        print_stmt = [&](std::unique_ptr<HAFLSL::Statement>& stmt){
            if(ImGui::TreeNode((std::string{stmt->get_name().data()} + "##" + std::to_string(stmt->uuid)).c_str())) {
                if (ImGui::IsItemClicked()) {
                    is_stmt = true;
                    is_expr = false;
                    selected_stmt = stmt.get();
                    selected_expr = nullptr;
                }

                switch(stmt->get_type()) {
                    case HAFLSL::StatementType::BreakStatement: {
                        break;
                    }
                    case HAFLSL::StatementType::ContinueStatement: {
                        break;
                    }
                    case HAFLSL::StatementType::DiscardStatement: {
                        break;
                    }
                    case HAFLSL::StatementType::ReturnStatement: {
                        auto* s = dynamic_cast<HAFLSL::ReturnStatement*>(stmt.get());
                        print_expr(s->expr);

                        break;
                    }
                    case HAFLSL::StatementType::DeclareFunctionStatement: {
                        auto* s = dynamic_cast<HAFLSL::DeclareFunctionStatement*>(stmt.get());
                        for(auto& a : s->statements) {
                            print_stmt(a);
                        }

                        break;
                    }
                    case HAFLSL::StatementType::DeclareStructStatement: {
                        break;
                    }
                    case HAFLSL::StatementType::DeclareVariableStatement: {
                        auto* s = dynamic_cast<HAFLSL::DeclareVariableStatement*>(stmt.get());
                        print_expr(s->expression);

                        break;
                    }
                    case HAFLSL::StatementType::MultiStatement: {
                        break;
                    }
                    case HAFLSL::StatementType::ScopedStatement: {
                        break;
                    }
                    case HAFLSL::StatementType::BranchStatement: {
                        break;
                    }
                    case HAFLSL::StatementType::WhileStatement: {
                        break;
                    }
                    case HAFLSL::StatementType::ForStatement: {
                        break;
                    }
                    case HAFLSL::StatementType::ExpressionStatement: {
                        auto* s = dynamic_cast<HAFLSL::ExpressionStatement*>(stmt.get());
                        print_expr(s->expression);
                        break;
                    }
                    case HAFLSL::StatementType::LocationStatement: {
                        break;
                    }
                }

                ImGui::TreePop();
            }
        };

        ImGui::Begin("AST viewer");
        if(ImGui::TreeNode("Root Node")) {
            for(auto& node : ast.statements) {
                print_stmt(node);
            }

            ImGui::TreePop();
        }
        ImGui::End();

        ImGui::Begin("SPIRV out");
        ImGui::TextWrapped("%s", spirv_dissambly.c_str());
        ImGui::End();

        ImGui::Begin("Node viewer");
        ImGui::Text("Node type: %s", is_stmt ? "Statement" : "Expression");

        std::string_view name = "";
        HAFLSL::UUID uuid(0);
        if(selected_stmt) {
            name = selected_stmt->get_name();
            uuid = selected_stmt->uuid;
        }

        if(selected_expr) {
            name = selected_expr->get_name();
            uuid = selected_expr->uuid;
        }

        ImGui::Text("Node name: %s", name.data());
        ImGui::Text("Node UUID: %lu", static_cast<u64>(uuid));

        if(selected_stmt) {
            switch(selected_stmt->get_type()) {
                case HAFLSL::StatementType::BreakStatement: {
                    break;
                }
                case HAFLSL::StatementType::ContinueStatement: {
                    break;
                }
                case HAFLSL::StatementType::DiscardStatement: {
                    break;
                }
                case HAFLSL::StatementType::ReturnStatement: {
                    break;
                }
                case HAFLSL::StatementType::DeclareFunctionStatement: {
                    auto* s = dynamic_cast<HAFLSL::DeclareFunctionStatement*>(selected_stmt);
                    ImGui::Text("Name: %s", std::string{s->name}.c_str());
                    ImGui::Text("Returned type: %s", HAFLSL::Lexer::token_to_string_view(s->returned_type).data());

                    break;
                }
                case HAFLSL::StatementType::DeclareStructStatement: {
                    break;
                }
                case HAFLSL::StatementType::DeclareVariableStatement: {
                    auto* s = dynamic_cast<HAFLSL::DeclareVariableStatement*>(selected_stmt);
                    ImGui::Text("Name: %s", std::string{s->name}.c_str());
                    //ImGui::Text("Type: %s", HAFLSL::Lexer::token_to_string_view(s->type).data());
                    ImGui::Text("Value: %s", HAFLSL::Lexer::token_to_string_view(s->type).data());
                    break;
                }
                case HAFLSL::StatementType::MultiStatement: {
                    break;
                }
                case HAFLSL::StatementType::ScopedStatement: {
                    break;
                }
                case HAFLSL::StatementType::BranchStatement: {
                    break;
                }
                case HAFLSL::StatementType::WhileStatement: {
                    break;
                }
                case HAFLSL::StatementType::ForStatement: {
                    break;
                }
                case HAFLSL::StatementType::ExpressionStatement: {
                    break;
                }
                case HAFLSL::StatementType::LocationStatement: {
                    auto* s = dynamic_cast<HAFLSL::LocationStatement*>(selected_stmt);

                    ImGui::Text("Location: %i", static_cast<i32>(s->location));
                    ImGui::Text("Way: %s", s->way.type == HAFLSL::TokenType::IN ? "in" : "out");
                    ImGui::Text("Type: %s", HAFLSL::Lexer::token_to_string_view(s->type).data());
                    ImGui::Text("Name: %s", std::string{s->name}.c_str());
                    break;
                }
            }
        }

        if(selected_expr) {
            switch(selected_expr->get_type()) {
                case HAFLSL::ExpressionType::ConstantValueExpression: {
                    auto* e = dynamic_cast<HAFLSL::ConstantValueExpression*>(selected_expr);

                    std::string value = {};
                    switch(e->token.type) {
                        case HAFLSL::TokenType::FLOATCONSTANT:
                            value = std::to_string(std::get<f64>(e->token.data));
                            break;
                        case HAFLSL::TokenType::INTCONSTANT:
                            value = std::to_string(std::get<i64>(e->token.data));
                            break;
                        case HAFLSL::TokenType::UINTCONSTANT:
                            value = std::to_string(std::get<u64>(e->token.data));
                            break;
                        case HAFLSL::TokenType::BOOLCONSTANT:
                            value = std::get<bool>(e->token.data) ? "true": "false";
                            break;
                        case HAFLSL::TokenType::DOUBLECONSTANT:
                            value = std::to_string(std::get<f64>(e->token.data));
                            break;
                        case HAFLSL::TokenType::IDENTIFIER:
                            value = std::string{std::get<std::string_view>(e->token.data)};
                            break;
                        default:
                            value = "wtf";
                            break;
                    }

                    ImGui::Text("Type: %s", value.c_str());

                    break;
                }
                case HAFLSL::ExpressionType::BinaryExpression: {
                    break;
                }
                case HAFLSL::ExpressionType::UnaryExpression: {
                    break;
                }
                case HAFLSL::ExpressionType::IdentifierExpression: {
                    break;
                }
                case HAFLSL::ExpressionType::AccessIdentifierExpression: {
                    break;
                }
                case HAFLSL::ExpressionType::AccessIndexExpression: {
                    break;
                }
                case HAFLSL::ExpressionType::AssignExpression: {
                    auto* e = dynamic_cast<HAFLSL::AssignExpression*>(selected_expr);
                    
                    std::string assign_type = {};
                    switch(e->type) {
                        case HAFLSL::AssignType::Simple:                assign_type += "=";  break;
                        case HAFLSL::AssignType::CompoundAdd:           assign_type += "+=";  break;
                        case HAFLSL::AssignType::CompoundSubtract:      assign_type += "-=";  break;
                        case HAFLSL::AssignType::CompoundMultiply:      assign_type += "*=";  break;
                        case HAFLSL::AssignType::CompoundDivide:        assign_type += "/=";  break;
                        case HAFLSL::AssignType::CompoundModulo:        assign_type += "%=";  break;
                        case HAFLSL::AssignType::CompoundBitShiftLeft:  assign_type += "<<=";  break;
                        case HAFLSL::AssignType::CompoundBitShiftRight: assign_type += ">>=";  break;
                        case HAFLSL::AssignType::CompoundBitAnd:        assign_type += "&=";  break;
                        case HAFLSL::AssignType::CompoundBitExOr:       assign_type += "^=";  break;
                        case HAFLSL::AssignType::CompoundBitInOr:       assign_type += "|=";  break;
                        default:                                assign_type += "wtf";  break;
                    }
                    
                    ImGui::Text("Type: %s", assign_type.c_str());

                    break;
                }
                case HAFLSL::ExpressionType::CallFunctionExpression: {
                    break;
                }
                case HAFLSL::ExpressionType::ConstructorExpression: {
                    auto* e = dynamic_cast<HAFLSL::ConstructorExpression*>(selected_expr);

                    ImGui::Text("Type: %s", HAFLSL::Lexer::token_to_string_view(e->type).data());

                    break;
                }
            }
        }
        ImGui::End();

        ImGui::Render();
    }

    void on_update() {
        ui_update();

        render();
    }

    void render() {
        daxa::ImageId swapchain_image = swapchain.acquire_next_image();
        if (swapchain_image.is_empty()) {
            return;
        }

        daxa::CommandList cmd_list = device.create_command_list({ .debug_name = "main loop cmd list"});

        cmd_list.pipeline_barrier_image_transition({
            .waiting_pipeline_access = daxa::AccessConsts::TRANSFER_WRITE,
            .before_layout = daxa::ImageLayout::UNDEFINED,
            .after_layout = daxa::ImageLayout::TRANSFER_DST_OPTIMAL,
            .image_id = swapchain_image
        });

        cmd_list.begin_renderpass({
            .color_attachments = {{
                .image_view = swapchain_image.default_view(),
                .load_op = daxa::AttachmentLoadOp::CLEAR,
                .clear_value = std::array<daxa::f32, 4>{0.10f, 0.10f, 0.10f, 1.00f},
            }},
            .render_area = {.x = 0, .y = 0, .width = size_x, .height = size_y},
        });
        cmd_list.set_pipeline(*raster_pipeline);
        cmd_list.draw({.vertex_count = 3});
        cmd_list.end_renderpass();

        imgui_renderer.record_commands(ImGui::GetDrawData(), cmd_list, swapchain_image, size_x, size_y);

        cmd_list.pipeline_barrier_image_transition({
            .awaited_pipeline_access = daxa::AccessConsts::ALL_GRAPHICS_READ_WRITE,
            .before_layout = daxa::ImageLayout::TRANSFER_DST_OPTIMAL,
            .after_layout = daxa::ImageLayout::PRESENT_SRC,
            .image_id = swapchain_image
        });

        cmd_list.complete();
        device.submit_commands({
            .command_lists = {std::move(cmd_list)},
            .wait_binary_semaphores = {swapchain.get_acquire_semaphore()},
            .signal_binary_semaphores = {swapchain.get_present_semaphore()},
            .signal_timeline_semaphores = {{swapchain.get_gpu_timeline_semaphore(), swapchain.get_cpu_timeline_value()}}
        });

        device.present_frame({
            .wait_binary_semaphores = { swapchain.get_present_semaphore()},
            .swapchain = swapchain
        });
    }

    void on_mouse_move(f32 x, f32 y) {}
    void on_mouse_scroll(f32 x, f32 y) {}
    void on_mouse_button(int key, int action) {}
    void on_key(int key, int action) {}

    void on_resize(u32 sx, u32 sy) {
        minimized = (sx == 0 || sy == 0);
        if (!minimized) {
            swapchain.resize();
            size_x = swapchain.get_surface_extent().x;
            size_y = swapchain.get_surface_extent().y;

            on_update();
        }
    }
    void toggle_pause() {
        glfwSetCursorPos(glfw_window_ptr, static_cast<f64>(size_x / 2), static_cast<f64>(size_y / 2));
        glfwSetInputMode(glfw_window_ptr, GLFW_CURSOR, paused ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
        glfwSetInputMode(glfw_window_ptr, GLFW_RAW_MOUSE_MOTION, paused);
        paused = !paused;
    }
};

int main() {
    App app = {};
    while (true) {
        if (app.update())
            break;
    }

    return 0;
}