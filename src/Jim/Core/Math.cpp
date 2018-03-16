#include "./Math.h"
#include "./Types.h"

using namespace Jim::Core::Types;
using namespace Jim::Core::Math;

const unit Jim::Core::Math::PI = 3.1415926535897932384626433832795;
const unit Jim::Core::Math::E = 2.7182818284590452353602874713527;

unit Jim::Core::Math::degToRad(unit deg) {
    return (deg != 0) ? deg / 180 * PI : 0;
}

unit Jim::Core::Math::radToDeg(unit rad) {
    return (rad != 0) ?  rad * 180 / PI : 0;
}
