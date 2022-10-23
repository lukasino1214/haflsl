#include <haflsl/lexer.hpp>
#include <haflsl/logger.hpp>
#include <fast_float/fast_float.h>
#include <charconv>

namespace HAFLSL {
    Lexer::Lexer() {
        keywords["const"] = TokenType::CONST;
        keywords["bool"] = TokenType::BOOL;
        keywords["float"] = TokenType::FLOAT;
        keywords["int"] = TokenType::INT;
        keywords["uint"] = TokenType::UINT;
        keywords["double"] = TokenType::DOUBLE;
        keywords["bvec2"] = TokenType::BVEC2;
        keywords["bvec3"] = TokenType::BVEC3;
        keywords["bvec4"] = TokenType::BVEC4;
        keywords["ivec2"] = TokenType::IVEC2;
        keywords["ivec3"] = TokenType::IVEC3;
        keywords["ivec4"] = TokenType::IVEC4;
        keywords["uvec2"] = TokenType::UVEC2;
        keywords["uvec3"] = TokenType::UVEC3;
        keywords["uvec4"] = TokenType::UVEC4;
        keywords["vec2"] = TokenType::VEC2;
        keywords["vec3"] = TokenType::VEC3;
        keywords["vec4"] = TokenType::VEC4;
        keywords["mat2"] = TokenType::MAT2;
        keywords["mat3"] = TokenType::MAT3;
        keywords["mat4"] = TokenType::MAT4;
        keywords["mat2x2"] = TokenType::MAT2X2;
        keywords["mat2x3"] = TokenType::MAT2X3;
        keywords["mat2x4"] = TokenType::MAT2X4;
        keywords["mat3x2"] = TokenType::MAT3X2;
        keywords["mat3x3"] = TokenType::MAT3X3;
        keywords["mat3x4"] = TokenType::MAT3X4;
        keywords["mat4x2"] = TokenType::MAT4X2;
        keywords["mat4x3"] = TokenType::MAT4X3;
        keywords["mat4x4"] = TokenType::MAT4X4;
        keywords["dvec2"] = TokenType::DVEC2;
        keywords["dvec3"] = TokenType::DVEC3;
        keywords["dvec4"] = TokenType::DVEC4;
        keywords["dmat2"] = TokenType::DMAT2;
        keywords["dmat3"] = TokenType::DMAT3;
        keywords["dmat4"] = TokenType::DMAT4;
        keywords["dmat2x2"] = TokenType::DMAT2X2;
        keywords["dmat2x3"] = TokenType::DMAT2X3;
        keywords["dmat2x4"] = TokenType::DMAT2X4;
        keywords["dmat3x2"] = TokenType::DMAT3X2;
        keywords["dmat3x3"] = TokenType::DMAT3X3;
        keywords["dmat3x4"] = TokenType::DMAT3X4;
        keywords["dmat4x2"] = TokenType::DMAT4X2;
        keywords["dmat4x3"] = TokenType::DMAT4X3;
        keywords["dmat4x4"] = TokenType::DMAT4X4;
        keywords["centroid"] = TokenType::CENTROID;
        keywords["in"] = TokenType::IN;
        keywords["out"] = TokenType::OUT;
        keywords["inout"] = TokenType::INOUT;
        keywords["uniform"] = TokenType::UNIFORM;
        keywords["patch"] = TokenType::PATCH;
        keywords["sample"] = TokenType::SAMPLE;
        keywords["buffer"] = TokenType::BUFFER;
        keywords["shared"] = TokenType::SHARED;
        keywords["coherent"] = TokenType::COHERENT;
        keywords["volatile"] = TokenType::VOLATILE;
        keywords["restrict"] = TokenType::RESTRICT;
        keywords["readonly"] = TokenType::READONLY;
        keywords["writeonly"] = TokenType::WRITEONLY;
        keywords["noperspective"] = TokenType::NOPERSPECTIVE;
        keywords["flat"] = TokenType::FLAT;
        keywords["smooth"] = TokenType::SMOOTH;
        keywords["layout"] = TokenType::LAYOUT;
        keywords["atomic_uint"] = TokenType::ATOMIC_UINT;
        keywords["sampler2D"] = TokenType::SAMPLER2D;
        keywords["sampler3D"] = TokenType::SAMPLER3D;
        keywords["samplerCube"] = TokenType::SAMPLERCUBE;
        keywords["sampler2DShadow"] = TokenType::SAMPLER2DSHADOW;
        keywords["samplerCubeShadow"] = TokenType::SAMPLERCUBESHADOW;
        keywords["sampler2DArray"] = TokenType::SAMPLER2DARRAY;
        keywords["sampler2DArrayShadow"] = TokenType::SAMPLER2DARRAYSHADOW;
        keywords["isampler2D"] = TokenType::ISAMPLER2D;
        keywords["isampler3D"] = TokenType::ISAMPLER3D;
        keywords["isamplerCube"] = TokenType::ISAMPLERCUBE;
        keywords["isampler2DArray"] = TokenType::ISAMPLER2DARRAY;
        keywords["usampler2D"] = TokenType::USAMPLER2D;
        keywords["usampler3D"] = TokenType::USAMPLER3D;
        keywords["usamplerCube"] = TokenType::USAMPLERCUBE;
        keywords["usampler2DArray"] = TokenType::USAMPLER2DARRAY;
        keywords["sampler1D"] = TokenType::SAMPLER1D;
        keywords["sampler1DShadow"] = TokenType::SAMPLER1DSHADOW;
        keywords["sampler1DArray"] = TokenType::SAMPLER1DARRAY;
        keywords["sampler1DArrayShadow"] = TokenType::SAMPLER1DARRAYSHADOW;
        keywords["isampler1D"] = TokenType::ISAMPLER1D;
        keywords["isampler1DArray"] = TokenType::ISAMPLER1DARRAY;
        keywords["usampler1D"] = TokenType::USAMPLER1D;
        keywords["usampler1DArray"] = TokenType::USAMPLER1DARRAY;
        keywords["sampler2DRect"] = TokenType::SAMPLER2DRECT;
        keywords["sampler2DRectShadow"] = TokenType::SAMPLER2DRECTSHADOW;
        keywords["isampler2DRect"] = TokenType::ISAMPLER2DRECT;
        keywords["usampler2DRect"] = TokenType::USAMPLER2DRECT;
        keywords["samplerBuffer"] = TokenType::SAMPLERBUFFER;
        keywords["isamplerBuffer"] = TokenType::ISAMPLERBUFFER;
        keywords["usamplerBuffer"] = TokenType::USAMPLERBUFFER;
        keywords["samplerCubeArray"] = TokenType::SAMPLERCUBEARRAY;
        keywords["samplerCubeArrayShadow"] = TokenType::SAMPLERCUBEARRAYSHADOW;
        keywords["isamplerCubeArray"] = TokenType::ISAMPLERCUBEARRAY;
        keywords["usamplerCubeArray"] = TokenType::USAMPLERCUBEARRAY;
        keywords["isamplerCube"] = TokenType::ISAMPLERCUBE;
        keywords["usamplerCube"] = TokenType::USAMPLERCUBE;
        keywords["sampler2DMS"] = TokenType::SAMPLER2DMS;
        keywords["isampler2DMS"] = TokenType::ISAMPLER2DMS;
        keywords["usampler2DMS"] = TokenType::USAMPLER2DMS;
        keywords["sampler2DMSArray"] = TokenType::SAMPLER2DMSARRAY;
        keywords["isampler2DMSArray"] = TokenType::ISAMPLER2DMSARRAY;
        keywords["usampler2DMSArray"] = TokenType::USAMPLER2DMSARRAY;
        keywords["image2D"] = TokenType::IMAGE2D;
        keywords["iimage2D"] = TokenType::IIMAGE2D;
        keywords["uimage2D"] = TokenType::UIMAGE2D;
        keywords["image3D"] = TokenType::IMAGE3D;
        keywords["iimage3D"] = TokenType::IIMAGE3D;
        keywords["uimage3D"] = TokenType::UIMAGE3D;
        keywords["imageCube"] = TokenType::IMAGECUBE;
        keywords["iimageCube"] = TokenType::IIMAGECUBE;
        keywords["uimageCube"] = TokenType::UIMAGECUBE;
        keywords["imageBuffer"] = TokenType::IMAGEBUFFER;
        keywords["iimageBuffer"] = TokenType::IIMAGEBUFFER;
        keywords["uimageBuffer"] = TokenType::UIMAGEBUFFER;
        keywords["image2DArray"] = TokenType::IMAGE2DARRAY;
        keywords["iimage2DArray"] = TokenType::IIMAGE2DARRAY;
        keywords["uimage2DArray"] = TokenType::UIMAGE2DARRAY;
        keywords["imageCubeArray"] = TokenType::IMAGECUBEARRAY;
        keywords["iimageCubeArray"] = TokenType::IIMAGECUBEARRAY;
        keywords["uimageCubeArray"] = TokenType::UIMAGECUBEARRAY;
        keywords["image1D"] = TokenType::IMAGE1D;
        keywords["iimage1D"] = TokenType::IIMAGE1D;
        keywords["uimage1D"] = TokenType::UIMAGE1D;
        keywords["image1DArray"] = TokenType::IMAGE1DARRAY;
        keywords["iimage1DArray"] = TokenType::IIMAGE1DARRAY;
        keywords["uimage1DArray"] = TokenType::UIMAGE1DARRAY;
        keywords["image2DRect"] = TokenType::IMAGE2DRECT;
        keywords["iimage2DRect"] = TokenType::IIMAGE2DRECT;
        keywords["uimage2DRect"] = TokenType::UIMAGE2DRECT;
        keywords["image2DMS"] = TokenType::IMAGE2DMS;
        keywords["iimage2DMS"] = TokenType::IIMAGE2DMS;
        keywords["uimage2DMS"] = TokenType::UIMAGE2DMS;
        keywords["image2DMSArray"] = TokenType::IMAGE2DMSARRAY;
        keywords["iimage2DMSArray"] = TokenType::IIMAGE2DMSARRAY;
        keywords["uimage2DMSArray"] = TokenType::UIMAGE2DMSARRAY;
        keywords["struct"] = TokenType::STRUCT;
        keywords["void"] = TokenType::VOID;
        keywords["while"] = TokenType::WHILE;
        keywords["break"] = TokenType::BREAK;
        keywords["continue"] = TokenType::CONTINUE;
        keywords["do"] = TokenType::DO;
        keywords["else"] = TokenType::ELSE;
        keywords["for"] = TokenType::FOR;
        keywords["if"] = TokenType::IF;
        keywords["discard"] = TokenType::DISCARD;
        keywords["return"] = TokenType::RETURN;
        keywords["switch"] = TokenType::SWITCH;
        keywords["case"] = TokenType::CASE;
        keywords["default"] = TokenType::DEFAULT;
        keywords["subroutine"] = TokenType::SUBROUTINE;
        keywords["invariant"] = TokenType::INVARIANT;
        keywords["precise"] = TokenType::PRECISE;
        keywords["highp"] = TokenType::HIGH_PRECISION;
        keywords["mediump"] = TokenType::MEDIUM_PRECISION;
        keywords["lowp"] = TokenType::LOW_PRECISION;
        keywords["precision"] = TokenType::PRECISION;
    }

    auto Lexer::tokenize(const std::string& src) -> std::vector<Token> {
        std::vector<Token> tokens;
        bool string = false;
        u32 pos = 0;
        for(u32 i = 0; i < src.size(); i++) {
            if(src[i] != ' ' && src[i] != '\n') {
                switch(src[i]) {
                    case '<':
                        if(src[i+1] == '<') {
                            if(src[i+2] == '=') {
                                tokens.push_back({TokenType::LEFT_ASSIGN, i, 3});
                                i += 2;
                                break;
                            } else {
                                tokens.push_back({TokenType::LEFT_OP, i, 2});
                                i += 1;
                                break;
                            }
                        } else if(src[i+1] == '=') {
                            tokens.push_back({TokenType::LE_OP, i, 2});
                            i += 1;
                            break;
                        } else {
                            tokens.push_back({TokenType::LEFT_ANGLE, i, 1});
                            break;
                        }
                    case '>':
                        if(src[i+1] == '>') {
                            if(src[i+2] == '=') {
                                tokens.push_back({TokenType::RIGHT_ASSIGN, i, 3});
                                i += 2;
                                break;
                            } else {
                                tokens.push_back({TokenType::RIGHT_OP, i, 2});
                                i += 1;
                                break;
                            }
                        } else if(src[i+1] == '=') {
                            tokens.push_back({TokenType::GE_OP, i, 2});
                            i += 1;
                            break;
                        } else {
                            tokens.push_back({TokenType::RIGHT_ANGLE, i, 1});
                            break;
                        }
                    case '+':
                        if(src[i+1] == '+') {
                            tokens.push_back({TokenType::INC_OP, i, 2});
                            i += 1;
                            break;
                        } else if (src[i+1] == '=') {
                            tokens.push_back({TokenType::ADD_ASSIGN, i, 2});
                            i += 1;
                            break;
                        } else {
                            tokens.push_back({TokenType::PLUS, i, 1});
                            break;
                        }
                    case '-':
                        if(src[i+1] == '-') {
                            tokens.push_back({TokenType::DEC_OP, i, 2});
                            i += 1;
                            break;
                        } else if (src[i+1] == '=') {
                            tokens.push_back({TokenType::SUB_ASSIGN, i, 2});
                            i += 1;
                            break;
                        } else {
                            tokens.push_back({TokenType::DASH, i, 1});
                            break;
                        }
                    case '=':
                        if(src[i+1] == '=') {
                            tokens.push_back({TokenType::EQ_OP, i, 2});
                            i += 1;
                            break;
                        } else {
                            tokens.push_back({TokenType::EQUAL, i, 1});
                            break;
                        }
                    case '!':
                        if(src[i+1] == '=') {
                            tokens.push_back({TokenType::NE_OP, i, 2});
                            i += 1;
                            break;
                        } else {
                            tokens.push_back({TokenType::BANG, i, 1});
                            break;
                        }
                    case '&':
                        if(src[i+1] == '&') {
                            tokens.push_back({TokenType::AND_OP, i, 2});
                            i += 1;
                            break;
                        } else if (src[i+1] == '=') {
                            tokens.push_back({TokenType::AND_ASSIGN, i, 2});
                            i += 1;
                            break;
                        } else {
                            tokens.push_back({TokenType::AMPERSAND, i, 1});
                            break;
                        }
                    case '|':
                        if(src[i+1] == '|') {
                            tokens.push_back({TokenType::OR_OP, i, 2});
                            i += 1;
                            break;
                        } else if (src[i+1] == '=') {
                            tokens.push_back({TokenType::OR_ASSIGN, i, 2});
                            i += 1;
                            break;
                        } else {
                            tokens.push_back({TokenType::VERTICAL_BAR, i, 1});
                            break;
                        }
                    case '^':
                        if(src[i+1] == '^') {
                            tokens.push_back({TokenType::XOR_OP, i, 2});
                            i += 1;
                            break;
                        } else if (src[i+1] == '=') {
                            tokens.push_back({TokenType::XOR_ASSIGN, i, 2});
                            i += 1;
                            break;
                        } else {
                            tokens.push_back({TokenType::CARET, i, 1});
                            break;
                        }
                    case '*':
                        if(src[i+1] == '=') {
                            tokens.push_back({TokenType::MUL_ASSIGN, i, 2});
                            i += 1;
                            break;
                        } else {
                            tokens.push_back({TokenType::STAR, i, 1});
                            break;
                        }
                    case '/':
                        if(src[i+1] == '=') {
                            tokens.push_back({TokenType::DIV_ASSIGN, i, 2});
                            i += 1;
                            break;
                        } else {
                            tokens.push_back({TokenType::SLASH, i, 1});
                            break;
                        }
                    case '%':
                        if(src[i+1] == '=') {
                            tokens.push_back({TokenType::MOD_ASSIGN, i, 2});
                            i += 1;
                            break;
                        } else {
                            tokens.push_back({TokenType::PERCENT, i, 1});
                            break;
                        }
                    case '(':
                        tokens.push_back({TokenType::LEFT_PAREN, i, 1});
                        break;
                    case ')':
                        tokens.push_back({TokenType::RIGHT_PAREN, i, 1});
                        break;
                    case '[':
                        tokens.push_back({TokenType::LEFT_BRACKET, i, 1});
                        break;
                    case ']':
                        tokens.push_back({TokenType::RIGHT_BRACKET, i, 1});
                        break;
                    case '{':
                        tokens.push_back({TokenType::LEFT_BRACE, i, 1});
                        break;
                    case '}':
                        tokens.push_back({TokenType::RIGHT_BRACE, i, 1});
                        break;
                    case '.':
                        tokens.push_back({TokenType::DOT, i, 1});
                        break;
                    case ',':
                        tokens.push_back({TokenType::COMMA, i, 1});
                        break;
                    case ':':
                        tokens.push_back({TokenType::COLON, i, 1});
                        break;
                    case ';':
                        tokens.push_back({TokenType::SEMICOLON, i, 1});
                        break;
                    case '~':
                        tokens.push_back({TokenType::TILDE, i, 1});
                        break;
                    case '?':
                        tokens.push_back({TokenType::QUESTION, i, 1});
                        break;
                    default:
                        u32 pos = i;
                        bool found_number = false;
                        switch(src[pos]) {
                            case '0' ... '9':
                                found_number = true;
                                break;
                            default:
                                break;
                        }
                        while(true) {
                            if(src[pos] == ' ' || src[pos] == '(' || src[pos] == '=' || src[pos] == ')' || src[pos] == ',' || src[pos] == '\n') {
                                Token token {
                                    .type = TokenType::IDENTIFIER,
                                    .index = i,
                                    .len =  pos - i,
                                    .data = std::string_view{src.data() + i, pos - i}
                                };
                                tokens.push_back(std::move(token));

                                i = pos - 1;
                                break;
                            } else if(!found_number && src[pos] == '.') {
                                Token token {
                                    .type = TokenType::IDENTIFIER,
                                    .index = i,
                                    .len =  pos - i,
                                    .data = std::string_view{src.data() + i, pos - i}
                                };
                                tokens.push_back(std::move(token));

                                i = pos - 1;
                                break;
                            }
                            pos++;
                        }
                        break;
                }
            }
        }

        // check identifiers if they are not some token
        for(auto& token : tokens) {
            if(token.type == TokenType::IDENTIFIER) {
                std::string view{src.data() + token.index, token.len};
                if(keywords.find(view) != keywords.end()) {
                token.type = keywords.at(view);
                }
            }
        }

        std::vector<std::string_view> structs;

        for(u32 i = 0; i < tokens.size(); i++) {
            if(tokens[i].type == TokenType::IDENTIFIER) {
                std::string view{src.data() + tokens[i].index, tokens[i].len};
                if(view == "true") {
                    tokens[i].type = TokenType::BOOLCONSTANT;
                    tokens[i].data = true;
                    continue;
                }

                if(view == "false") {
                    tokens[i].type = TokenType::BOOLCONSTANT;
                    tokens[i].data = false;
                    continue;
                }


                bool found_dot = false; 
                bool hexadecimal = false;
                bool found_float = false;
                bool found_uint = false;
                bool is_number = false;
                bool fix = false;
                for(u32 j = 0; j < tokens[i].len; j++) {
                    switch(src[tokens[i].index + j]) {
                        case '0' ... '9':
                            if(j == 0) {
                                is_number = true;
                            }
                            break;
                        default:
                            if(is_number) {
                                if(j == 1) {
                                    if(src[tokens[i].index + j] == 'X' || src[tokens[i].index + j] == 'x' || src[tokens[i].index] == '0') {
                                        hexadecimal = true;
                                        continue;
                                    }
                                }
                                if(j == tokens[i].len - 1) {
                                    if(src[tokens[i].index + j] == 'U' || src[tokens[i].index + j] == 'u') {
                                        found_uint = true;
                                        fix = true;
                                        continue;
                                    } else if(src[tokens[i].index + j] == 'F' || src[tokens[i].index + j] == 'f') {
                                        found_float = true;
                                        fix = true;
                                        continue;
                                    } 
                                    else {
                                        INFO("error");
                                    }
                                }
                                if(src[tokens[i].index + j] == '.') {
                                    found_dot = true;
                                    continue;
                                }
                            }

                            break;
                    }
                }

                if(is_number) {
                    if(found_dot) {
                        f64 value;
						fast_float::from_chars_result r = fast_float::from_chars(src.data() + tokens[i].index, src.data() + tokens[i].index + tokens[i].len - fix, value);
						if (r.ptr == src.data() + tokens[i].index + tokens[i].len - fix && r.ec == std::errc{}) {
                            INFO("{}", value);
                            tokens[i].data = value;
                        } else if (r.ec == std::errc::result_out_of_range) {
                            INFO("result out of range");
                        } else {
                            INFO("bad number");
                        }

                        if(found_float) {
                            tokens[i].type = TokenType::FLOATCONSTANT;
                        } else {
                            tokens[i].type = TokenType::DOUBLECONSTANT;
                        }
                    } else {
                        i64 value;
						std::from_chars_result r = std::from_chars(src.data() + tokens[i].index, src.data() + tokens[i].index + tokens[i].len - fix, value, (hexadecimal) ? 16 : 10);
						if (r.ptr == src.data() + tokens[i].index + tokens[i].len - fix && r.ec == std::errc{}) {
                            INFO("{}", value);
                        } else if (r.ec == std::errc::result_out_of_range) {
                            INFO("result out of range");
                        } else {
                            INFO("bad number");
                        }

                        if(found_uint) {
                            tokens[i].type = TokenType::UINTCONSTANT;
                            tokens[i].data = static_cast<u64>(value);
                        } else {
                            tokens[i].type = TokenType::INTCONSTANT;
                            tokens[i].data = value;
                        }
                    }
                }
            }
            
            if(i != 0) {
                if(tokens[i-1].type == TokenType::DOT) {
                    tokens[i].type = TokenType::FIELD_SELECTION;
                    continue;
                }

                if(tokens[i-1].type == TokenType::STRUCT) {
                    tokens[i].type = TokenType::TYPE_NAME;
                    structs.emplace_back(src.data() + tokens[i].index, tokens[i].len);
                    continue;
                }

                if(tokens[i].type == TokenType::IDENTIFIER) {
                    std::string view{src.data() + tokens[i].index, tokens[i].len};
                    for(auto& s : structs) {
                        if(view == s) {
                            tokens[i].type = TokenType::TYPE_NAME;
                            continue;
                        }
                    }
                }
            }
        }

        return tokens;
    }

    void Lexer::print_token(const std::string& src, const Token& token) {
        switch(token.type) {
            case TokenType::CONST:
                INFO("TOKEN TYPE: CONST \t\t\t VALUE: const");
                break;
            case TokenType::BOOL:
                INFO("TOKEN TYPE: BOOL \t\t\t VALUE: bool");
                break;
            case TokenType::FLOAT:
                INFO("TOKEN TYPE: FLOAT \t\t\t VALUE: float");
                break;
            case TokenType::INT:
                INFO("TOKEN TYPE: INT \t\t\t VALUE: int");
                break;
            case TokenType::UINT:
                INFO("TOKEN TYPE: UINT \t\t\t VALUE: uint");
                break;
            case TokenType::DOUBLE:
                INFO("TOKEN TYPE: DOUBLE \t\t\t VALUE: double");
                break;
            case TokenType::BVEC2:
                INFO("TOKEN TYPE: BVEC2 \t\t\t VALUE: bvec2");
                break;
            case TokenType::BVEC3:
                INFO("TOKEN TYPE: BVEC3 \t\t\t VALUE: bvec3");
                break;
            case TokenType::BVEC4:
                INFO("TOKEN TYPE: BVEC4 \t\t\t VALUE: bvec4");
                break;
            case TokenType::IVEC2:
                INFO("TOKEN TYPE: IVEC2 \t\t\t VALUE: ivec2");
                break;
            case TokenType::IVEC3:
                INFO("TOKEN TYPE: IVEC3 \t\t\t VALUE: ivec3");
                break;
            case TokenType::IVEC4:
                INFO("TOKEN TYPE: IVEC4 \t\t\t VALUE: ivec4");
                break;
            case TokenType::UVEC2:
                INFO("TOKEN TYPE: UVEC2 \t\t\t VALUE: uvec2");
                break;
            case TokenType::UVEC3:
                INFO("TOKEN TYPE: UVEC3 \t\t\t VALUE: uvec3");
                break;
            case TokenType::UVEC4:
                INFO("TOKEN TYPE: UVEC4 \t\t\t VALUE: uvec4");
                break;
            case TokenType::VEC2:
                INFO("TOKEN TYPE: VEC2 \t\t\t VALUE: vec2");
                break;
            case TokenType::VEC3:
                INFO("TOKEN TYPE: VEC3 \t\t\t VALUE: vec3");
                break;
            case TokenType::VEC4:
                INFO("TOKEN TYPE: VEC4 \t\t\t VALUE: vec4");
                break;
            case TokenType::MAT2:
                INFO("TOKEN TYPE: MAT2 \t\t\t VALUE: mat2"); 
                break;
            case TokenType::MAT3:
                INFO("TOKEN TYPE: MAT3 \t\t\t VALUE: mat3"); 
                break;
            case TokenType::MAT4:
                INFO("TOKEN TYPE: MAT4 \t\t\t VALUE: mat4"); 
                break;
            case TokenType::MAT2X2:
                INFO("TOKEN TYPE: MAT2X2 \t\t\t VALUE: mat2x2"); 
                break;
            case TokenType::MAT2X3:
                INFO("TOKEN TYPE: MAT2X3 \t\t\t VALUE: mat2x3"); 
                break;
            case TokenType::MAT2X4:
                INFO("TOKEN TYPE: MAT2X4 \t\t\t VALUE: mat2x4"); 
                break;
            case TokenType::MAT3X2:
                INFO("TOKEN TYPE: MAT3X2 \t\t\t VALUE: mat3x2"); 
                break;
            case TokenType::MAT3X3:
                INFO("TOKEN TYPE: MAT3X3 \t\t\t VALUE: mat3x3"); 
                break;
            case TokenType::MAT3X4:
                INFO("TOKEN TYPE: MAT3X4 \t\t\t VALUE: mat3x4"); 
                break;
            case TokenType::MAT4X2:
                INFO("TOKEN TYPE: MAT4X2 \t\t\t VALUE: mat4x2"); 
                break;
            case TokenType::MAT4X3:
                INFO("TOKEN TYPE: MAT4X3 \t\t\t VALUE: mat4x3"); 
                break;
            case TokenType::MAT4X4:
                INFO("TOKEN TYPE: MAT4X4 \t\t\t VALUE: mat4x4"); 
                break;
            case TokenType::DVEC2:
                INFO("TOKEN TYPE: DVEC2 \t\t\t VALUE: dvec2"); 
                break;
            case TokenType::DVEC3:
                INFO("TOKEN TYPE: DVEC3 \t\t\t VALUE: dvec3"); 
                break;
            case TokenType::DVEC4:
                INFO("TOKEN TYPE: DVEC4 \t\t\t VALUE: dvec4"); 
                break;
            case TokenType::DMAT2:
                INFO("TOKEN TYPE: DMAT2 \t\t\t VALUE: dmat2"); 
                break;
            case TokenType::DMAT3:
                INFO("TOKEN TYPE: DMAT3 \t\t\t VALUE: dmat3"); 
                break;
            case TokenType::DMAT4:
                INFO("TOKEN TYPE: DMAT4 \t\t\t VALUE: dmat4"); 
                break;
            case TokenType::DMAT2X2:
                INFO("TOKEN TYPE: DMAT2X2 \t\t\t VALUE: dmat2x2"); 
                break;
            case TokenType::DMAT2X3:
                INFO("TOKEN TYPE: DMAT2X3 \t\t\t VALUE: dmat2x3"); 
                break;
            case TokenType::DMAT2X4:
                INFO("TOKEN TYPE: DMAT2X4 \t\t\t VALUE: dmat2x4"); 
                break;
            case TokenType::DMAT3X2:
                INFO("TOKEN TYPE: DMAT3X2 \t\t\t VALUE: dmat3x2"); 
                break;
            case TokenType::DMAT3X3:
                INFO("TOKEN TYPE: DMAT3X3 \t\t\t VALUE: dmat3x3"); 
                break;
            case TokenType::DMAT3X4:
                INFO("TOKEN TYPE: DMAT3X4 \t\t\t VALUE: dmat3x4"); 
                break;
            case TokenType::DMAT4X2:
                INFO("TOKEN TYPE: DMAT4X2 \t\t\t VALUE: dmat4x2"); 
                break;
            case TokenType::DMAT4X3:
                INFO("TOKEN TYPE: DMAT4X3 \t\t\t VALUE: dmat4x3"); 
                break;
            case TokenType::DMAT4X4:
                INFO("TOKEN TYPE: DMAT4X4 \t\t\t VALUE: dmat4x4"); 
                break;
            case TokenType::CENTROID:
                INFO("TOKEN TYPE: CENTROID \t\t VALUE: centroid"); 
                break;
            case TokenType::IN:
                INFO("TOKEN TYPE: IN \t\t\t VALUE: in"); 
                break;
            case TokenType::OUT:
                INFO("TOKEN TYPE: OUT \t\t\t VALUE: out"); 
                break;
            case TokenType::INOUT:
                INFO("TOKEN TYPE: INOUT \t\t\t VALUE: inout"); 
                break;
            case TokenType::UNIFORM:
                INFO("TOKEN TYPE: UNIFORM \t\t\t VALUE: uniform"); 
                break;
            case TokenType::PATCH:
                INFO("TOKEN TYPE: PATCH \t\t\t VALUE: patch"); 
                break;
            case TokenType::SAMPLE:
                INFO("TOKEN TYPE: SAMPLE \t\t\t VALUE: sample"); 
                break;
            case TokenType::BUFFER:
                INFO("TOKEN TYPE: BUFFER \t\t VALUE: buffer"); 
                break;
            case TokenType::SHARED:
                INFO("TOKEN TYPE: SHARED \t\t\t VALUE: shared"); 
                break;
            case TokenType::COHERENT:
                INFO("TOKEN TYPE: COHERENT \t\t VALUE: coherent"); 
                break;
            case TokenType::VOLATILE:
                INFO("TOKEN TYPE: VOLATILE \t\t VALUE: volatile"); 
                break;
            case TokenType::RESTRICT:
                INFO("TOKEN TYPE: RESTRICT \t\t VALUE: restrict"); 
                break;
            case TokenType::READONLY:
                INFO("TOKEN TYPE: READONLY \t\t VALUE: readonly"); 
                break;
            case TokenType::WRITEONLY:
                INFO("TOKEN TYPE: WRITEONLY \t\t VALUE: writeonly"); 
                break;
            case TokenType::NOPERSPECTIVE:
                INFO("TOKEN TYPE: NOPERSPECTIVE \t\t VALUE: noperspective"); 
                break;
            case TokenType::FLAT:
                INFO("TOKEN TYPE: FLAT \t\t\t VALUE: flat"); 
                break;
            case TokenType::SMOOTH:
                INFO("TOKEN TYPE: SMOOTH \t\t\t VALUE: smooth"); 
                break;
            case TokenType::LAYOUT:
                INFO("TOKEN TYPE: LAYOUT \t\t\t VALUE: layout"); 
                break;
            case TokenType::ATOMIC_UINT:
                INFO("TOKEN TYPE: ATOMIC_UINT \t\t VALUE: atomic_uint"); 
                break;
            case TokenType::SAMPLER2D:
                INFO("TOKEN TYPE: SAMPLER2D \t\t VALUE: sampler2D"); 
                break;
            case TokenType::SAMPLER3D:
                INFO("TOKEN TYPE: SAMPLER3D \t\t VALUE: sampler3D"); 
                break;
            case TokenType::SAMPLERCUBE:
                INFO("TOKEN TYPE: SAMPLERCUBE \t\t VALUE: samplerCube"); 
                break;
            case TokenType::SAMPLER2DSHADOW:
                INFO("TOKEN TYPE: SAMPLER2DSHADOW \t\t VALUE: sampler2DShadow"); 
                break;
            case TokenType::SAMPLERCUBESHADOW:
                INFO("TOKEN TYPE: SAMPLERCUBESHADOW \t VALUE: samplerCubeShadow"); 
                break;
            case TokenType::SAMPLER2DARRAY:
                INFO("TOKEN TYPE: SAMPLER2DARRAY \t\t VALUE: sampler2DArray"); 
                break;
            case TokenType::SAMPLER2DARRAYSHADOW:
                INFO("TOKEN TYPE: SAMPLER2DARRAYSHADOW \t VALUE: sampler2DArrayShadow"); 
                break;
            case TokenType::ISAMPLER2D:
                INFO("TOKEN TYPE: ISAMPLER2D \t\t VALUE: isampler2D"); 
                break;
            case TokenType::ISAMPLER3D:
                INFO("TOKEN TYPE: ISAMPLER3D \t\t VALUE: isampler3D"); 
                break;
            case TokenType::ISAMPLERCUBE:
                INFO("TOKEN TYPE: ISAMPLERCUBE \t\t VALUE: isamplerCube"); 
                break;
            case TokenType::ISAMPLER2DARRAY:
                INFO("TOKEN TYPE: ISAMPLER2DARRAY \t\t VALUE: isampler2DArray"); 
                break;
            case TokenType::USAMPLER2D:
                INFO("TOKEN TYPE: USAMPLER2D \t\t VALUE: usampler2D"); 
                break;
            case TokenType::USAMPLER3D:
                INFO("TOKEN TYPE: USAMPLER3D \t\t VALUE: usampler3D"); 
                break;
            case TokenType::USAMPLERCUBE:
                INFO("TOKEN TYPE: USAMPLERCUBE \t\t VALUE: usamplerCube"); 
                break;
            case TokenType::USAMPLER2DARRAY:
                INFO("TOKEN TYPE: USAMPLER2DARRAY \t\t VALUE: usampler2DArray"); 
                break;
            case TokenType::SAMPLER1D:
                INFO("TOKEN TYPE: SAMPLER1D \t\t VALUE: sampler1D"); 
                break;
            case TokenType::SAMPLER1DSHADOW:
                INFO("TOKEN TYPE: SAMPLER1DSHADOW \t\t VALUE: sampler1DShadow"); 
                break;
            case TokenType::SAMPLER1DARRAY:
                INFO("TOKEN TYPE: SAMPLER1DARRAY \t\t VALUE: sampler1DArray"); 
                break;
            case TokenType::SAMPLER1DARRAYSHADOW:
                INFO("TOKEN TYPE: SAMPLER1DARRAYSHADOW \t VALUE: sampler1DArrayShadow"); 
                break;
            case TokenType::ISAMPLER1D:
                INFO("TOKEN TYPE: ISAMPLER1D \t\t VALUE: isampler1D"); 
                break;
            case TokenType::ISAMPLER1DARRAY:
                INFO("TOKEN TYPE: ISAMPLER1DARRAY \t\t VALUE: isampler1DArray"); 
                break;
            case TokenType::USAMPLER1D:
                INFO("TOKEN TYPE: USAMPLER1D \t\t VALUE: usampler1D"); 
                break;
            case TokenType::USAMPLER1DARRAY:
                INFO("TOKEN TYPE: USAMPLER1DARRAY \t\t VALUE: usampler1DArray"); 
                break;
            case TokenType::SAMPLER2DRECT:
                INFO("TOKEN TYPE: SAMPLER2DRECT \t\t VALUE: sampler2DRect"); 
                break;
            case TokenType::SAMPLER2DRECTSHADOW:
                INFO("TOKEN TYPE: SAMPLER2DRECTSHADOW \t VALUE: sampler2DRectShadow"); 
                break;
            case TokenType::ISAMPLER2DRECT:
                INFO("TOKEN TYPE: ISAMPLER2DRECT \t\t VALUE: isampler2DRect"); 
                break;
            case TokenType::USAMPLER2DRECT:
                INFO("TOKEN TYPE: USAMPLER2DRECT \t\t VALUE: usampler2DRect"); 
                break;
            case TokenType::SAMPLERBUFFER:
                INFO("TOKEN TYPE: SAMPLERBUFFER \t\t VALUE: samplerBuffer"); 
                break;
            case TokenType::ISAMPLERBUFFER:
                INFO("TOKEN TYPE: ISAMPLERBUFFER \t\t VALUE: isamplerBuffer"); 
                break;
            case TokenType::USAMPLERBUFFER:
                INFO("TOKEN TYPE: USAMPLERBUFFER \t\t VALUE: usamplerBuffer"); 
                break;
            case TokenType::SAMPLERCUBEARRAY:
                INFO("TOKEN TYPE: SAMPLERCUBEARRAY \t VALUE: samplerCubeArray"); 
                break;
            case TokenType::SAMPLERCUBEARRAYSHADOW:
                INFO("TOKEN TYPE: SAMPLERCUBEARRAYSHADOW \t VALUE: samplerCubeArrayShadow"); 
                break;
            case TokenType::ISAMPLERCUBEARRAY:
                INFO("TOKEN TYPE: ISAMPLERCUBEARRAY \t VALUE: isamplerCubeArray"); 
                break;
            case TokenType::USAMPLERCUBEARRAY:
                INFO("TOKEN TYPE: USAMPLERCUBEARRAY \t VALUE: usamplerCubeArray"); 
                break;
            case TokenType::SAMPLER2DMS:
                INFO("TOKEN TYPE: SAMPLER2DMS \t\t VALUE: sampler2DMS"); 
                break;
            case TokenType::ISAMPLER2DMS:
                INFO("TOKEN TYPE: ISAMPLER2DMS \t\t VALUE: isampler2DMS"); 
                break;
            case TokenType::USAMPLER2DMS:
                INFO("TOKEN TYPE: USAMPLER2DMS \t\t VALUE: usampler2DMS"); 
                break;
            case TokenType::SAMPLER2DMSARRAY:
                INFO("TOKEN TYPE: SAMPLER2DMSARRAY \t VALUE: sampler2DMSArray"); 
                break;
            case TokenType::ISAMPLER2DMSARRAY:
                INFO("TOKEN TYPE: ISAMPLER2DMSARRAY \t VALUE: isampler2DMSArray"); 
                break;
            case TokenType::USAMPLER2DMSARRAY:
                INFO("TOKEN TYPE: USAMPLER2DMSARRAY \t VALUE: usampler2DMSArray"); 
                break;
            case TokenType::IMAGE2D:
                INFO("TOKEN TYPE: IMAGE2D \t\t\t VALUE: image2D"); 
                break;
            case TokenType::IIMAGE2D:
                INFO("TOKEN TYPE: IIMAGE2D \t\t VALUE: iimage2D"); 
                break;
            case TokenType::UIMAGE2D:
                INFO("TOKEN TYPE: UIMAGE2D \t\t VALUE: uimage2D"); 
                break;
            case TokenType::IMAGE3D:
                INFO("TOKEN TYPE: IMAGE3D \t\t\t VALUE: image3D"); 
                break;
            case TokenType::IIMAGE3D:
                INFO("TOKEN TYPE: IIMAGE3D \t\t VALUE: iimage3D"); 
                break;
            case TokenType::UIMAGE3D:
                INFO("TOKEN TYPE: UIMAGE3D \t\t VALUE: uimage3D"); 
                break;
            case TokenType::IMAGECUBE:
                INFO("TOKEN TYPE: IMAGECUBE \t\t VALUE: imageCube"); 
                break;
            case TokenType::IIMAGECUBE:
                INFO("TOKEN TYPE: IIMAGECUBE \t\t VALUE: iimageCube"); 
                break;
            case TokenType::UIMAGECUBE:
                INFO("TOKEN TYPE: UIMAGECUBE \t\t VALUE: uimageCube"); 
                break;
            case TokenType::IMAGEBUFFER:
                INFO("TOKEN TYPE: IMAGEBUFFER \t\t VALUE: imageBuffer"); 
                break;
            case TokenType::IIMAGEBUFFER:
                INFO("TOKEN TYPE: IIMAGEBUFFER \t\t VALUE: iimageBuffer"); 
                break;
            case TokenType::UIMAGEBUFFER:
                INFO("TOKEN TYPE: UIMAGEBUFFER \t\t VALUE: uimageBuffer"); 
                break;
            case TokenType::IMAGE2DARRAY:
                INFO("TOKEN TYPE: IMAGE2DARRAY \t\t VALUE: image2DArray"); 
                break;
            case TokenType::IIMAGE2DARRAY:
                INFO("TOKEN TYPE: IIMAGE2DARRAY \t\t VALUE: iimage2DArray"); 
                break;
            case TokenType::UIMAGE2DARRAY:
                INFO("TOKEN TYPE: UIMAGE2DARRAY \t\t VALUE: uimage2DArray"); 
                break;
            case TokenType::IMAGECUBEARRAY:
                INFO("TOKEN TYPE: IMAGECUBEARRAY \t\t VALUE: imageCubeArray"); 
                break;
            case TokenType::IIMAGECUBEARRAY:
                INFO("TOKEN TYPE: IIMAGECUBEARRAY \t\t VALUE: iimageCubeArray"); 
                break;
            case TokenType::UIMAGECUBEARRAY:
                INFO("TOKEN TYPE: UIMAGECUBEARRAY \t\t VALUE: uimageCubeArray"); 
                break;
            case TokenType::IMAGE1D:
                INFO("TOKEN TYPE: IMAGE1D \t\t\t VALUE: image1D"); 
                break;
            case TokenType::IIMAGE1D:
                INFO("TOKEN TYPE: IIMAGE1D \t\t VALUE: iimage1D"); 
                break;
            case TokenType::UIMAGE1D:
                INFO("TOKEN TYPE: UIMAGE1D \t\t VALUE: uimage1D"); 
                break;
            case TokenType::IMAGE1DARRAY:
                INFO("TOKEN TYPE: IMAGE1DARRAY \t\t VALUE: image1DArray"); 
                break;
            case TokenType::IIMAGE1DARRAY:
                INFO("TOKEN TYPE: IIMAGE1DARRAY \t\t VALUE: iimage1DArray"); 
                break;
            case TokenType::UIMAGE1DARRAY:
                INFO("TOKEN TYPE: UIMAGE1DARRAY \t\t VALUE: uimage1DArray"); 
                break;
            case TokenType::IMAGE2DRECT:
                INFO("TOKEN TYPE: IMAGE2DRECT \t\t VALUE: image2DRect"); 
                break;
            case TokenType::IIMAGE2DRECT:
                INFO("TOKEN TYPE: IIMAGE2DRECT \t\t VALUE: iimage2DRect"); 
                break;
            case TokenType::UIMAGE2DRECT:
                INFO("TOKEN TYPE: UIMAGE2DRECT \t\t VALUE: uimage2DRect"); 
                break;
            case TokenType::IMAGE2DMS:
                INFO("TOKEN TYPE: IMAGE2DMS \t\t VALUE: image2DMS"); 
                break;
            case TokenType::IIMAGE2DMS:
                INFO("TOKEN TYPE: IIMAGE2DMS \t\t VALUE: iimage2DMS"); 
                break;
            case TokenType::UIMAGE2DMS:
                INFO("TOKEN TYPE: UIMAGE2DMS \t\t VALUE: uimage2DMS"); 
                break;
            case TokenType::IMAGE2DMSARRAY:
                INFO("TOKEN TYPE: IMAGE2DMSARRAY \t\t VALUE: image2DMSArray"); 
                break;
            case TokenType::IIMAGE2DMSARRAY:
                INFO("TOKEN TYPE: IIMAGE2DMSARRAY \t\t VALUE: iimage2DMSArray"); 
                break;
            case TokenType::UIMAGE2DMSARRAY:
                INFO("TOKEN TYPE: UIMAGE2DMSARRAY \t\t VALUE: uimage2DMSArray"); 
                break;
            case TokenType::STRUCT:
                INFO("TOKEN TYPE: STRUCT \t\t\t VALUE: struct"); 
                break;
            case TokenType::VOID:
                INFO("TOKEN TYPE: VOID \t\t\t VALUE: void"); 
                break;
            case TokenType::WHILE:
                INFO("TOKEN TYPE: WHILE \t\t\t VALUE: while"); 
                break;
            case TokenType::BREAK:
                INFO("TOKEN TYPE: BREAK \t\t\t VALUE: break"); 
                break;
            case TokenType::CONTINUE:
                INFO("TOKEN TYPE: CONTINUE \t\t VALUE: continue"); 
                break;
            case TokenType::DO:
                INFO("TOKEN TYPE: DO \t\t\t VALUE: do"); 
                break;
            case TokenType::ELSE:
                INFO("TOKEN TYPE: ELSE \t\t\t VALUE: else"); 
                break;
            case TokenType::FOR:
                INFO("TOKEN TYPE: FOR \t\t\t VALUE: for"); 
                break;
            case TokenType::IF:
                INFO("TOKEN TYPE: IF \t\t\t VALUE: if"); 
                break;
            case TokenType::DISCARD:
                INFO("TOKEN TYPE: DISCARD \t\t\t VALUE: discard"); 
                break;
            case TokenType::RETURN:
                INFO("TOKEN TYPE: RETURN \t\t\t VALUE: return"); 
                break;
            case TokenType::SWITCH:
                INFO("TOKEN TYPE: SWITCH \t\t\t VALUE: switch"); 
                break;
            case TokenType::CASE:
                INFO("TOKEN TYPE: CASE \t\t\t VALUE: case"); 
                break;
            case TokenType::DEFAULT:
                INFO("TOKEN TYPE: DEFAULT \t\t\t VALUE: default"); 
                break;
            case TokenType::SUBROUTINE:
                INFO("TOKEN TYPE: SUBROUTINE \t\t VALUE: subroutine"); 
                break;
            case TokenType::IDENTIFIER:
                INFO("TOKEN TYPE: IDENTIFIER \t\t VALUE: {:s}", src.substr(token.index, token.len)); 
                break;
            case TokenType::TYPE_NAME:
                INFO("TOKEN TYPE: TYPE_NAME \t\t VALUE: {:s}", src.substr(token.index, token.len)); 
                break;
            case TokenType::FLOATCONSTANT:
                INFO("TOKEN TYPE: FLOATCONSTANT \t\t VALUE: {:s}", src.substr(token.index, token.len)); 
                break;
            case TokenType::INTCONSTANT:
                INFO("TOKEN TYPE: INTCONSTANT \t\t VALUE: {:s}", src.substr(token.index, token.len)); 
                break;
            case TokenType::UINTCONSTANT:
                INFO("TOKEN TYPE: UINTCONSTANT \t\t VALUE: {:s}", src.substr(token.index, token.len)); 
                break;
            case TokenType::BOOLCONSTANT:
                INFO("TOKEN TYPE: BOOLCONSTANT \t\t VALUE: {:s}", std::get<bool>(token.data) ? "true" : "false"); 
                break;
            case TokenType::DOUBLECONSTANT:
                INFO("TOKEN TYPE: DOUBLECONSTANT \t\t VALUE: {:s}", src.substr(token.index, token.len)); 
                break;
            case TokenType::FIELD_SELECTION:
                INFO("TOKEN TYPE: FIELD_SELECTION \t\t VALUE: {:s}", src.substr(token.index, token.len)); 
                break;
            case TokenType::LEFT_OP:
                INFO("TOKEN TYPE: LEFT_OP \t\t\t VALUE: <<");
                break;
            case TokenType::RIGHT_OP:
                INFO("TOKEN TYPE: RIGHT_OP \t\t VALUE: >>");
                break;
            case TokenType::INC_OP:
                INFO("TOKEN TYPE: INC_OP \t\t\t VALUE: ++");
                break;
            case TokenType::DEC_OP:
                INFO("TOKEN TYPE: DEC_OP \t\t\t VALUE: --");
                break;
            case TokenType::LE_OP:
                INFO("TOKEN TYPE: LE_OP \t\t\t VALUE: <=");
                break;
            case TokenType::GE_OP:
                INFO("TOKEN TYPE: GE_OP \t\t\t VALUE: >=");
                break;
            case TokenType::EQ_OP:
                INFO("TOKEN TYPE: EQ_OP \t\t\t VALUE: ==");
                break;
            case TokenType::NE_OP:
                INFO("TOKEN TYPE: NE_OP \t\t\t VALUE: !=");
                break;
            case TokenType::AND_OP:
                INFO("TOKEN TYPE: AND_OP \t\t\t VALUE: &&");
                break;
            case TokenType::OR_OP:
                INFO("TOKEN TYPE: OR_OP \t\t\t VALUE: ||");
                break;
            case TokenType::XOR_OP:
                INFO("TOKEN TYPE: XOR_OP \t\t\t VALUE: ^^");
                break;
            case TokenType::MUL_ASSIGN:
                INFO("TOKEN TYPE: MUL_ASSIGN \t\t VALUE: *=");
                break;
            case TokenType::DIV_ASSIGN:
                INFO("TOKEN TYPE: DIV_ASSIGN \t\t VALUE: /=");
                break;
            case TokenType::ADD_ASSIGN:
                INFO("TOKEN TYPE: ADD_ASSIGN \t\t VALUE: +=");
                break;
            case TokenType::MOD_ASSIGN:
                INFO("TOKEN TYPE: MOD_ASSIGN \t\t VALUE: %=");
                break;
            case TokenType::LEFT_ASSIGN:
                INFO("TOKEN TYPE: LEFT_ASSIGN \t\t VALUE: <<=");
                break;
            case TokenType::RIGHT_ASSIGN:
                INFO("TOKEN TYPE: RIGHT_ASSIGN \t\t VALUE: >>=");
                break;
            case TokenType::AND_ASSIGN:
                INFO("TOKEN TYPE: AND_ASSIGN \t\t VALUE: &=");
                break;
            case TokenType::XOR_ASSIGN:
                INFO("TOKEN TYPE: XOR_ASSIGN \t\t VALUE: ^=");
                break;
            case TokenType::OR_ASSIGN:
                INFO("TOKEN TYPE: OR_ASSIGN \t\t VALUE: |=");
                break;
            case TokenType::SUB_ASSIGN:
                INFO("TOKEN TYPE: SUB_ASSIGN \t\t VALUE: -=");
                break;
            case TokenType::LEFT_PAREN:
                INFO("TOKEN TYPE: LEFT_PAREN \t\t VALUE: (");
                break;
            case TokenType::RIGHT_PAREN:
                INFO("TOKEN TYPE: RIGHT_PAREN \t\t VALUE: )");
                break;
            case TokenType::LEFT_BRACKET:
                INFO("TOKEN TYPE: LEFT_BRACKET \t\t VALUE: [");
                break;
            case TokenType::RIGHT_BRACKET:
                INFO("TOKEN TYPE: RIGHT_BRACKET \t\t VALUE: ]");
                break;
            case TokenType::LEFT_BRACE:
                INFO("TOKEN TYPE: LEFT_BRACE \t\t VALUE: {");
                break;
            case TokenType::RIGHT_BRACE:
                INFO("TOKEN TYPE: RIGHT_BRACE \t\t VALUE: }");
                break;
            case TokenType::DOT:
                INFO("TOKEN TYPE: DOT \t\t\t VALUE: .");
                break;
            case TokenType::COMMA:
                INFO("TOKEN TYPE: COMMA \t\t\t VALUE: ,");
                break;
            case TokenType::COLON:
                INFO("TOKEN TYPE: COLON \t\t\t VALUE: :");
                break;
            case TokenType::EQUAL:
                INFO("TOKEN TYPE: EQUAL \t\t\t VALUE: =");
                break;
            case TokenType::SEMICOLON:
                INFO("TOKEN TYPE: SEMICOLON \t\t VALUE: ;");
                break;
            case TokenType::BANG:
                INFO("TOKEN TYPE: BANG \t\t\t VALUE: !");
                break;
            case TokenType::DASH:
                INFO("TOKEN TYPE: DASH \t\t\t VALUE: -");
                break;
            case TokenType::TILDE:
                INFO("TOKEN TYPE: TILDE \t\t\t VALUE: ~");
                break;
            case TokenType::PLUS:
                INFO("TOKEN TYPE: PLUS \t\t\t VALUE: +");
                break;
            case TokenType::STAR:
                INFO("TOKEN TYPE: STAR \t\t\t VALUE: *");
                break;
            case TokenType::SLASH:
                INFO("TOKEN TYPE: SLASH \t\t\t VALUE: /");
                break;
            case TokenType::PERCENT:
                INFO("TOKEN TYPE: PERCENT \t\t\t VALUE: %");
                break;
            case TokenType::LEFT_ANGLE:
                INFO("TOKEN TYPE: LEFT_ANGLE \t\t VALUE: <");
                break;
            case TokenType::RIGHT_ANGLE:
                INFO("TOKEN TYPE: RIGHT_ANGLE \t\t VALUE: >");
                break;
            case TokenType::VERTICAL_BAR:
                INFO("TOKEN TYPE: VERTICAL_BAR \t\t VALUE: |");
                break;
            case TokenType::CARET:
                INFO("TOKEN TYPE: CARET \t\t\t VALUE: ^");
                break;
            case TokenType::AMPERSAND:
                INFO("TOKEN TYPE: AMPERSAND \t\t VALUE: &");
                break;
            case TokenType::QUESTION:
                INFO("TOKEN TYPE: QUESTION \t\t VALUE: ?");
                break;
            case TokenType::INVARIANT:
                INFO("TOKEN TYPE: INVARIANT \t\t VALUE: invariant");
                break;
            case TokenType::PRECISE:
                INFO("TOKEN TYPE: PRECISE \t\t\t VALUE: precise");
                break;
            case TokenType::HIGH_PRECISION:
                INFO("TOKEN TYPE: HIGH_PRECISION \t\t VALUE: highp");
                break;
            case TokenType::MEDIUM_PRECISION:
                INFO("TOKEN TYPE: MEDIUM_PRECISION \t VALUE: mediump");
                break;
            case TokenType::LOW_PRECISION:
                INFO("TOKEN TYPE: LOW_PRECISION \t\t VALUE: lowp");
                break;
            case TokenType::PRECISION:
                INFO("TOKEN TYPE: PRECISION \t\t VALUE: precision");
                break;
            default:
                INFO("TOKEN TYPE: UNKNOWN  \t VALUE: UNKNOWN");
                break;   
        }
    }
}