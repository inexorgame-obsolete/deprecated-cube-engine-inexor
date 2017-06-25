
#include "inexor/gamemode/gamemode.hpp"
#include "inexor/shared/cube_vector.hpp"
#include "inexor/shared/cube_loops.hpp"


bool searchmodename(const char *haystack, const char *needle)
{
    if(!needle[0]) return true;
    do
    {
        if(needle[0] != '.')
        {
            haystack = strchr(haystack, needle[0]);
            if(!haystack) break;
            haystack++;
        }
        const char *h = haystack, *n = needle+1;
        for(; *h && *n; h++)
        {
            if(*h == *n) n++;
            else if(*h != ' ') break;
        }
        if(!*n) return true;
        if(*n == '.') return !*h;
    } while(needle[0] != '.');
    return false;
}

int genmodemask(vector<char *> &modes)
{
    long modemask = 0;
    loopv(modes)
    {
        const char *mode = modes[i];
        int op = mode[0];
        switch(mode[0])
        {
            case '*':
                modemask |= (long)1<<NUMGAMEMODES;
                loopk(NUMGAMEMODES) if(m_checknot(k+STARTGAMEMODE, M_DEMO|M_EDIT|M_LOCAL)) modemask |= 1<<k;
                continue;
            case '!':
                mode++;
                if(mode[0] != '?') break;
            case '?':
                mode++;
                loopk(NUMGAMEMODES) if(searchmodename(gamemodes[k].name, mode))
                {
                    if(op == '!') modemask &= ~(1<<k);
                    else modemask |= 1<<k;
                }
                continue;
        }
        int modenum = INT_MAX;
        if(isdigit(mode[0])) modenum = atoi(mode);
        else loopk(NUMGAMEMODES) if(searchmodename(gamemodes[k].name, mode)) { modenum = k+STARTGAMEMODE; break; }
        if(!m_valid(modenum)) continue;
        switch(op)
        {
            case '!': modemask &= ~(1 << (modenum - STARTGAMEMODE)); break;
            default: modemask |= 1 << (modenum - STARTGAMEMODE); break;
        }
    }
    return modemask;
}

const char *modename(int n, const char *unknown)
{
    if(m_valid(n)) return gamemodes[n - STARTGAMEMODE].name;
    return unknown;
}
