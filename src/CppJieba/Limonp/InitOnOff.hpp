#ifndef LIMONP_INITONOFF_H
#define LIMONP_INITONOFF_H

namespace Limonp
{
    class InitOnOff
    {
        public:
            InitOnOff(){_setInitFlag(false);};
            ~InitOnOff(){};
        protected:
            bool _isInited;
            bool _getInitFlag()const{return _isInited;};
            bool _setInitFlag(bool flag){return _isInited = flag;};
        public:
            operator bool() const {return _getInitFlag();};

    };
}

#endif
