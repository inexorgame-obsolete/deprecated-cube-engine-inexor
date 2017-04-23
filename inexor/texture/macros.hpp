#pragma once
#define writetex(t, body) \
        { \
        uchar *dstrow = t.data; \
        loop(y, t.h) \
                { \
            for(uchar *dst = dstrow, *end = &dstrow[t.w*t.bpp]; dst < end; dst += t.bpp) \
                        { \
                body; \
                        } \
            dstrow += t.pitch; \
                } \
        }

#define readwritetex(t, s, body) \
        { \
        uchar *dstrow = t.data, *srcrow = s.data; \
        loop(y, t.h) \
                { \
            for(uchar *dst = dstrow, *src = srcrow, *end = &srcrow[s.w*s.bpp]; src < end; dst += t.bpp, src += s.bpp) \
                        { \
                body; \
                        } \
            dstrow += t.pitch; \
            srcrow += s.pitch; \
                } \
        }

#define read2writetex(t, s1, src1, s2, src2, body) \
                { \
        uchar *dstrow = t.data, *src1row = s1.data, *src2row = s2.data; \
        loop(y, t.h) \
                                { \
            for(uchar *dst = dstrow, *end = &dstrow[t.w*t.bpp], *src1 = src1row, *src2 = src2row; dst < end; dst += t.bpp, src1 += s1.bpp, src2 += s2.bpp) \
                                    { \
                body; \
                                    } \
            dstrow += t.pitch; \
            src1row += s1.pitch; \
            src2row += s2.pitch; \
                                } \
                }


#define readwritergbtex(t, s, body) \
        { \
        if(t.bpp >= 3) { readwritetex(t, s, body); } \
                else \
                { \
            ImageData rgb(t.w, t.h, 3); \
            read2writetex(rgb, t, orig, s, src, \
                        { \
                switch(t.bpp) \
                                { \
                    case 1: dst[0] = orig[0]; dst[1] = orig[0]; dst[2] = orig[0]; break; \
                    case 2: dst[0] = orig[0]; dst[1] = orig[1]; dst[2] = orig[1]; break; \
                                } \
                body; \
                        }); \
            t.replace(rgb); \
                } \
        }

#define readwritergbatex(t, s, body) \
        { \
        if(t.bpp >= 4) { readwritetex(t, s, body); } \
                else \
                { \
            ImageData rgba(t.w, t.h, 4); \
            read2writetex(rgba, t, orig, s, src, \
                        { \
                switch(t.bpp) \
                                { \
                    case 1: dst[0] = orig[0]; dst[1] = orig[0]; dst[2] = orig[0]; break; \
                    case 2: dst[0] = orig[0]; dst[1] = orig[1]; dst[2] = orig[1]; break; \
                    case 3: dst[0] = orig[0]; dst[1] = orig[1]; dst[2] = orig[2]; break; \
                                } \
                body; \
                        }); \
            t.replace(rgba); \
                } \
        }
