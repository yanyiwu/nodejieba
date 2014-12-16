#ifndef LIMONP_CAST_FUNCTS_H
#define LIMONP_CAST_FUNCTS_H

namespace Limonp
{
    namespace CastFloat
    {
        //logical and or
        static const int sign_32 = 0xC0000000;
        static const int exponent_32 = 0x07800000;
        static const int mantissa_32 = 0x007FE000;
        static const int sign_exponent_32 = 0x40000000;
        static const int loss_32 = 0x38000000;

        static const short sign_16 = (short)0xC000;
        static const short exponent_16 = (short)0x3C00;
        static const short mantissa_16 = (short)0x03FF;
        static const short sign_exponent_16 = (short)0x4000;
        static const int exponent_fill_32 = 0x38000000;

        //infinite
        static const short infinite_16 = (short) 0x7FFF;
        static const short infinitesmall_16 = (short) 0x0000;

        inline float intBitsToFloat(unsigned int x)
        {
            union
            {
                float f;
                int i;
            }u;
            u.i = x;
            return u.f;
        }

        inline int floatToIntBits(float f)
        {
            union
            {
                float f;
                int i ;
            }u;
            u.f = f;
            return u.i;
        }

        inline short floatToShortBits(float f)
        {
            int fi = floatToIntBits(f);

            // 提取关键信息
            short sign = (short) ((unsigned int)(fi & sign_32) >> 16);
            short exponent = (short) ((unsigned int)(fi & exponent_32) >> 13);
            short mantissa = (short) ((unsigned int)(fi & mantissa_32) >> 13);
            // 生成编码结果
            short code = (short) (sign | exponent | mantissa);
            // 无穷大量、无穷小量的处理
            if ((fi & loss_32) > 0 && (fi & sign_exponent_32) > 0) {
                // 当指数符号为1时(正次方)，且左234位为1，返回无穷大量
                return (short) (code | infinite_16);
            }
            if (((fi & loss_32) ^ loss_32) > 0 && (fi & sign_exponent_32) == 0) {
                // 当指数符号位0时(负次方)，且左234位为0(与111异或>0)，返回无穷小量
                return infinitesmall_16;
            }

            return code;
        }

        inline float shortBitsToFloat(short s)
        {
            /*
             * 指数空余3位：若符号位为1，补0；若符号位为0，补1。 尾数位在后补0(13个)
             */
            int sign = ((int) (s & sign_16)) << 16;
            int exponent = ((int) (s & exponent_16)) << 13;
            // 指数符号位为0，234位补1
            if ((s & sign_exponent_16) == 0 && s != 0) {
                exponent |= exponent_fill_32;
            }
            int mantissa = ((int) (s & mantissa_16)) << 13;
            // 生成解码结果
            int code = sign | exponent | mantissa;
            return intBitsToFloat(code);

        }
    }
}

#endif
