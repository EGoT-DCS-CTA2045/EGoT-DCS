#include "DCMImpl.h"
#include "gmock/gmock.h"

class DCMImplMock : public DCMImpl {
    public:
        DCMImplMock():DCMImpl(){}
        MOCK_METHOD0(get_op_state,int());
};