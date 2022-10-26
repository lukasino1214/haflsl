#pragma once
#include "types.hpp"
#include <variant>
#include <string_view>

namespace HAFLSL {
    enum class TokenType : u32 {       
        CONST = 0, // const
        BOOL = 1, // bool
        FLOAT = 2, // float
        INT = 3, // int
        UINT = 4, // unit
        DOUBLE = 5, // double
        BVEC2 = 6, // bvec2
        BVEC3 = 7, // bvec3
        BVEC4 = 8, // bvec4
        IVEC2 = 9, // ivec2
        IVEC3 = 10, // ivec3
        IVEC4 = 11, // ivec4
        UVEC2 = 12, // uvec2
        UVEC3 = 13, // uvec3
        UVEC4 = 14, // uvec4
        VEC2 = 15, // vec2
        VEC3 = 16, // vec3
        VEC4 = 17, // vec4
        MAT2 = 18, // mat2
        MAT3 = 19, // mat3
        MAT4 = 20, // mat4
        MAT2X2 = 21, // mat2x2
        MAT2X3 = 22, // mat2x3
        MAT2X4 = 23, // mat2x4
        MAT3X2 = 24, // mat3x3
        MAT3X3 = 25, // mat3x3
        MAT3X4 = 26, // mat3x4
        MAT4X2 = 27, // mat4x2
        MAT4X3 = 28, // mat4x3
        MAT4X4 = 29, // mat4x4
        DVEC2 = 30, // dvec2
        DVEC3 = 31, // dvec3
        DVEC4 = 32, // dvec4
        DMAT2 = 33, // dmat2
        DMAT3 = 34, // dmat3
        DMAT4 = 35, // dmat4
        DMAT2X2 = 36, // dmat2x2
        DMAT2X3 = 37, // dmat2x3
        DMAT2X4 = 38, // dmat2x4
        DMAT3X2 = 39, // dmat3x2
        DMAT3X3 = 40, // dmat3x3
        DMAT3X4 = 41, // dmat3x4
        DMAT4X2 = 42, // dmat4x2
        DMAT4X3 = 43, // dmat4x3
        DMAT4X4 = 44, // dmat4x4
        CENTROID = 45, // centroid
        IN = 46, // in
        OUT = 47, // out
        INOUT = 48, // inout
        UNIFORM = 49, // uniform
        PATCH = 50, // patch
        SAMPLE = 51, // sample
        BUFFER = 52, // buffer
        SHARED = 53, // shared
        COHERENT = 54, // coherent
        VOLATILE = 55, // volatile
        RESTRICT = 56, // restrict
        READONLY = 57, // readonly
        WRITEONLY = 58, // writeonly
        NOPERSPECTIVE = 59, // noperspective
        FLAT = 60, // flat
        SMOOTH = 61, // smooth
        LAYOUT = 62, // layout
        ATOMIC_UINT = 63, // atomic_uint
        SAMPLER2D = 64, // sampler2D
        SAMPLER3D = 65, // sampler3D
        SAMPLERCUBE = 66, // samplerCube
        SAMPLER2DSHADOW = 67, // sampler2DShadow
        SAMPLERCUBESHADOW = 68, // samplerCubeShadow
        SAMPLER2DARRAY = 69, // sampler2DArray
        SAMPLER2DARRAYSHADOW = 70, // sampler2DArrayShadow
        ISAMPLER2D = 71, // isampler2D
        ISAMPLER3D = 72, // isampler3D
        ISAMPLERCUBE = 73, // isamplerCube
        ISAMPLER2DARRAY = 74, // isampler2DArray
        USAMPLER2D = 75, // usampler2D
        USAMPLER3D = 76, // usampler3D
        USAMPLERCUBE = 77, // usamplerCube
        USAMPLER2DARRAY = 78, // usampler2DArray
        SAMPLER1D = 79, // sampler1D
        SAMPLER1DSHADOW = 80, // sampler1DShadow
        SAMPLER1DARRAY = 81, // sampler1DArray
        SAMPLER1DARRAYSHADOW = 82, // sampler1DArrayShadow
        ISAMPLER1D = 83, // isampler1D
        ISAMPLER1DARRAY = 84, // isampler1DArray
        USAMPLER1D = 85, // usampler1D
        USAMPLER1DARRAY = 86, // usampler1DArray
        SAMPLER2DRECT = 87, // sampler2DRect
        SAMPLER2DRECTSHADOW = 88, // sampler2DRectShadow
        ISAMPLER2DRECT = 89, // isampler2DRect
        USAMPLER2DRECT = 90, // usampler2DRect
        SAMPLERBUFFER = 91, // samplerBuffer
        ISAMPLERBUFFER = 92, // isamplerBuffer
        USAMPLERBUFFER = 93, // usamplerBuffer
        SAMPLERCUBEARRAY = 94, // samplerCubeArray
        SAMPLERCUBEARRAYSHADOW = 95, // samplerCubeArrayShadow
        ISAMPLERCUBEARRAY = 96, // isamplerCube
        USAMPLERCUBEARRAY = 97, // usamplerCube
        SAMPLER2DMS = 98, // sampler2DMS
        ISAMPLER2DMS = 99, // isampler2DMS
        USAMPLER2DMS = 100, // usampler2DMS
        SAMPLER2DMSARRAY = 101, // sampler2DMSArray
        ISAMPLER2DMSARRAY = 102, // isampler2DMSArray
        USAMPLER2DMSARRAY = 103, // usampler2DMSArray
        IMAGE2D = 104, // image2D
        IIMAGE2D = 105, // iimage2D
        UIMAGE2D = 106, // uimage2D
        IMAGE3D = 107, // image3D
        IIMAGE3D = 108, // iimage3D
        UIMAGE3D = 109, // uimage3D
        IMAGECUBE = 110, // imageCube
        IIMAGECUBE = 111, // iimageCube
        UIMAGECUBE = 112, // uimageCube
        IMAGEBUFFER = 113, // imageBuffer
        IIMAGEBUFFER = 114, // iimageBuffer
        UIMAGEBUFFER = 115, // uimageBuffer
        IMAGE2DARRAY = 116, // image2DArray
        IIMAGE2DARRAY = 117, // iimage2DArray
        UIMAGE2DARRAY = 118, // uimage2DArray
        IMAGECUBEARRAY = 119, // imageCubeArray
        IIMAGECUBEARRAY = 120, // iimageCubeArray
        UIMAGECUBEARRAY = 121, // uimageCubeArray
        IMAGE1D = 122, // image1D
        IIMAGE1D = 123, // iimage1D
        UIMAGE1D = 124, // uimage1D
        IMAGE1DARRAY = 125, // image1DArray
        IIMAGE1DARRAY = 126, // iimage1DArray
        UIMAGE1DARRAY = 127, // uimage1DArray
        IMAGE2DRECT = 128, // image2DRect
        IIMAGE2DRECT = 129, // iimage2DRect
        UIMAGE2DRECT = 130, // uimage2DRect
        IMAGE2DMS = 131, // image2DMS
        IIMAGE2DMS = 132, // iimage2DMS
        UIMAGE2DMS = 133, // uimage2DMS
        IMAGE2DMSARRAY = 134, // image2DMSArray
        IIMAGE2DMSARRAY = 135, // iimage2DMSArray
        UIMAGE2DMSARRAY = 136, // uimage2DMSArray
        STRUCT = 137, // struct
        VOID = 138, // void
        WHILE = 139, // while
        BREAK = 140, // break
        CONTINUE = 141, // continue
        DO = 142, // do
        ELSE = 143, // else
        FOR = 144, // for
        IF = 145, // if
        DISCARD = 146, // discard
        RETURN = 147, // return
        SWITCH = 148, // switch
        CASE = 149, // case
        DEFAULT = 150, // default
        SUBROUTINE = 151, // subroutine
        IDENTIFIER = 152, // name 
        TYPE_NAME = 153, // user defined type like struct
        FLOATCONSTANT = 154, 
        INTCONSTANT = 155, 
        UINTCONSTANT = 156, 
        BOOLCONSTANT = 157, 
        DOUBLECONSTANT = 158, 
        FIELD_SELECTION = 159, // .x = 159, .xy = 159, .test
        LEFT_OP = 160, // <<
        RIGHT_OP = 161, // >>
        INC_OP = 162, // ++
        DEC_OP = 163, // --
        LE_OP = 164, // <=
        GE_OP = 165, // >=
        EQ_OP = 166, // ==
        NE_OP = 167, // !=
        AND_OP = 168, // &&
        OR_OP = 169, // ||
        XOR_OP = 170, // ^^
        MUL_ASSIGN = 171, // *=
        DIV_ASSIGN = 172, // /=
        ADD_ASSIGN = 173, // +=
        MOD_ASSIGN = 174, // %=
        LEFT_ASSIGN = 175, // <<=
        RIGHT_ASSIGN = 176, // >>=
        AND_ASSIGN = 177, // &=
        XOR_ASSIGN = 178, // ^=
        OR_ASSIGN = 179, // |=
        SUB_ASSIGN = 180, // -=
        LEFT_PAREN = 181, // (
        RIGHT_PAREN = 182, // )
        LEFT_BRACKET = 183, // [
        RIGHT_BRACKET = 184, // ]
        LEFT_BRACE = 185, // {
        RIGHT_BRACE = 186, // }
        DOT = 187, // .
        COMMA = 188, //  = 188,
        COLON = 189, // :
        EQUAL = 190, // =
        SEMICOLON = 191, // ;
        BANG = 192, // !
        DASH = 193, // -
        TILDE = 194, // ~
        PLUS = 195, // +
        STAR = 196, // *
        SLASH = 197, // /
        PERCENT = 198, // %
        LEFT_ANGLE = 199, // <
        RIGHT_ANGLE = 200, // >
        VERTICAL_BAR = 201, // |
        CARET = 202, // ^
        AMPERSAND = 203, // &
        QUESTION = 204, // ?
        INVARIANT = 205, // invariant
        PRECISE = 206, // precise 
        HIGH_PRECISION = 207, // highp
        MEDIUM_PRECISION = 208, // mediump
        LOW_PRECISION = 209, // lowp
        PRECISION = 210, // precision
    };

    struct Token {
        TokenType type;
        usize index, len;
        std::variant<std::monostate, u64, i64, f64, bool, std::string_view> data = std::monostate{};
    };
}