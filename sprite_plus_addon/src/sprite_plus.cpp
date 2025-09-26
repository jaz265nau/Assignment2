#include "sprite_plus.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <algorithm>
#include <cmath>

using namespace godot;

void SpritePlus::_bind_methods() {
    ClassDB::bind_method(D_METHOD("_process", "delta"), &SpritePlus::_process);

    ClassDB::bind_method(D_METHOD("set_enable_bob", "v"), &SpritePlus::set_enable_bob);
    ClassDB::bind_method(D_METHOD("get_enable_bob"), &SpritePlus::get_enable_bob);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "enable_bob"), "set_enable_bob", "get_enable_bob");

    ClassDB::bind_method(D_METHOD("set_bob_speed", "v"), &SpritePlus::set_bob_speed);
    ClassDB::bind_method(D_METHOD("get_bob_speed"), &SpritePlus::get_bob_speed);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "bob_speed", PROPERTY_HINT_RANGE, "0.0,10.0,0.1"), "set_bob_speed", "get_bob_speed");

    ClassDB::bind_method(D_METHOD("set_bob_amplitude", "v"), &SpritePlus::set_bob_amplitude);
    ClassDB::bind_method(D_METHOD("get_bob_amplitude"), &SpritePlus::get_bob_amplitude);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "bob_amplitude", PROPERTY_HINT_RANGE, "0.0,128.0,1.0"), "set_bob_amplitude", "get_bob_amplitude");

    ClassDB::bind_method(D_METHOD("set_enable_pulse", "v"), &SpritePlus::set_enable_pulse);
    ClassDB::bind_method(D_METHOD("get_enable_pulse"), &SpritePlus::get_enable_pulse);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "enable_pulse"), "set_enable_pulse", "get_enable_pulse");

    ClassDB::bind_method(D_METHOD("set_pulse_speed", "v"), &SpritePlus::set_pulse_speed);
    ClassDB::bind_method(D_METHOD("get_pulse_speed"), &SpritePlus::get_pulse_speed);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "pulse_speed", PROPERTY_HINT_RANGE, "0.0,10.0,0.1"), "set_pulse_speed", "get_pulse_speed");

    ClassDB::bind_method(D_METHOD("external_ping", "msg"), &SpritePlus::external_ping);

    ADD_SIGNAL(MethodInfo("out_of_bounds", PropertyInfo(Variant::VECTOR2, "position")));
}

void SpritePlus::_process(double delta) {
    if (!base_set) {
        base_y = get_position().y;
        base_set = true;
    }
    t += delta;

    Vector2 pos = get_position();

    if (enable_bob) {
        pos.y = base_y + static_cast<float>(std::sin(t * bob_speed) * bob_amplitude);
    }

    if (enable_pulse) {
        float s = 0.75f + 0.25f * std::sin(t * pulse_speed * 2.0);
        Color c = get_modulate();
        c.r = std::clamp(c.r * s, 0.0f, 1.0f);
        c.g = std::clamp(c.g * s, 0.0f, 1.0f);
        c.b = std::clamp(c.b * s, 0.0f, 1.0f);
        set_modulate(c);
    }

    set_position(pos);

    if (pos.x < -50.0f || pos.x > 2050.0f) {
        emit_signal("out_of_bounds", pos);
    }
}

void SpritePlus::external_ping(const String &msg) {
    UtilityFunctions::print("[SpritePlus] external_ping: ", msg);
    set_enable_bob(!get_enable_bob());
}