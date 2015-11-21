/// @file fl_time.h
/// @author Johannes Schneider
/// @brief Time format conversion tools


#ifndef INEXOR_VSCRIPT_TIME_TOOLS_HEADER
#define INEXOR_VSCRIPT_TIME_TOOLS_HEADER

namespace inexor {
namespace vscript {

    /// Inexor's VScript Engine supports various time formats
    enum INEXOR_VSCRIPT_TIME_FORMAT
    {
        TIME_FORMAT_MILISECONDS,
        TIME_FORMAT_SECONDS,
        TIME_FORMAT_MINUTES,
        TIME_FORMAT_HOURS
    };


    unsigned int ConvertTimeToMiliseconds(unsigned int interval, INEXOR_VSCRIPT_TIME_FORMAT format)
    {
        /// convert the interval into miliseconds
        switch(format)
        {
            case TIME_FORMAT_HOURS:
                interval *= 1000 * 60 *60;
                break;
            case TIME_FORMAT_MINUTES:
                interval *= 1000 * 60;
                break;
            case TIME_FORMAT_SECONDS:
                interval *= 1000;
                break;
            case TIME_FORMAT_MILISECONDS: 
                /// the engine's standard time format is miliseconds
                break;
        }
        return interval;
    }

};
};

#endif
