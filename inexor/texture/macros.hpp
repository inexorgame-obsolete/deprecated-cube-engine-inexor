
#define writetex(t, body) do \
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
        } while(0)

#define readwritetex(t, s, body) do \
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
        } while(0)

#define read2writetex(t, s1, src1, s2, src2, body) do \
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
                } while(0)


#define readwritergbtex(t, s, body) \
    { \
        if(t.bpp >= 3) readwritetex(t, s, body); \
        else \
        { \
            ImageData rgb(t.w, t.h, 3); \
            read2writetex(rgb, t, orig, s, src, { dst[0] = dst[1] = dst[2] = orig[0]; body; }); \
            t.replace(rgb); \
        } \
    }

#define readwritergbatex(t, s, body) \
    { \
        if(t.bpp >= 4) { readwritetex(t, s, body); } \
        else \
        { \
            ImageData rgba(t.w, t.h, 4); \
            if(t.bpp==3) read2writetex(rgba, t, orig, s, src, { dst[0] = orig[0]; dst[1] = orig[1]; dst[2] = orig[2]; body; }); \
            else read2writetex(rgba, t, orig, s, src, { dst[0] = dst[1] = dst[2] = orig[0]; body; }); \
            t.replace(rgba); \
        } \
    }
