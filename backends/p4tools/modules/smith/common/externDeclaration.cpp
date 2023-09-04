#include "backends/p4tools/modules/smith/common/externDeclaration.h"

#include "backends/p4tools/modules/smith/common/baseType.h"
#include "backends/p4tools/modules/smith/common/expression.h"
#include "backends/p4tools/modules/smith/common/functionDeclaration.h"
#include "backends/p4tools/modules/smith/common/parameterList.h"
#include "backends/p4tools/modules/smith/common/scope.h"
#include "backends/p4tools/modules/smith/common/typeRef.h"

namespace P4Tools {

namespace P4Smith {

IR::Method *externDeclaration::gen() {
    cstring name = randStr(7);
    IR::Type_Method *tm = nullptr;
    P4Scope::start_local_scope();
    IR::ParameterList *params = parameterList::gen();

    // externs have the same type restrictions as functions
    typeref_probs type_percent = {
        PCT.FUNCTIONDECLARATION_BASETYPE_BIT,    PCT.FUNCTIONDECLARATION_BASETYPE_SIGNED_BIT,
        PCT.FUNCTIONDECLARATION_BASETYPE_VARBIT, PCT.FUNCTIONDECLARATION_BASETYPE_INT,
        PCT.FUNCTIONDECLARATION_BASETYPE_ERROR,  PCT.FUNCTIONDECLARATION_BASETYPE_BOOL,
        PCT.FUNCTIONDECLARATION_BASETYPE_STRING, PCT.FUNCTIONDECLARATION_DERIVED_ENUM,
        PCT.FUNCTIONDECLARATION_DERIVED_HEADER,  PCT.FUNCTIONDECLARATION_DERIVED_HEADER_STACK,
        PCT.FUNCTIONDECLARATION_DERIVED_STRUCT,  PCT.FUNCTIONDECLARATION_DERIVED_HEADER_UNION,
        PCT.FUNCTIONDECLARATION_DERIVED_TUPLE,   PCT.FUNCTIONDECLARATION_TYPE_VOID,
        PCT.FUNCTIONDECLARATION_TYPE_MATCH_KIND,
    };
    IR::Type *return_type = typeRef::pick_rnd_type(type_percent);
    tm = new IR::Type_Method(return_type, params, name);
    auto ret = new IR::Method(name, tm);
    P4Scope::end_local_scope();
    P4Scope::add_to_scope(ret);
    return ret;
}

}  // namespace P4Smith

}  // namespace P4Tools
