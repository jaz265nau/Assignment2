#pragma once
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/color.hpp>
#include <godot_cpp/variant/vector2.hpp>

using namespace godot;

class SpritePlus : public Sprite2D {
    GDCLASS(SpritePlus, Sprite2D);

    // Feature A: bobbing
    bool   enable_bob = true;
    double bob_speed = 1.0;
    double bob_amplitude = 16.0;
    double t = 0.0;
    float  base_y = 0.f;
    bool   base_set = false;

    // Feature B: color pulse
    bool   enable_pulse = true;
    double pulse_speed = 1.0;

protected:
    static void _bind_methods();

public:
    void _process(double delta) override;

    void set_enable_bob(bool v) { enable_bob = v; }
    bool get_enable_bob() const { return enable_bob; }

    void set_bob_speed(double v) { bob_speed = v; }
    double get_bob_speed() const { return bob_speed; }

    void set_bob_amplitude(double v) { bob_amplitude = v; }
    double get_bob_amplitude() const { return bob_amplitude; }

    void set_enable_pulse(bool v) { enable_pulse = v; }
    bool get_enable_pulse() const { return enable_pulse; }

    void set_pulse_speed(double v) { pulse_speed = v; }
    double get_pulse_speed() const { return pulse_speed; }

    // method other nodes can trigger via signal
    void external_ping(const String &msg);
};