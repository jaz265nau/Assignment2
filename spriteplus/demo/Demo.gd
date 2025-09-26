extends Node2D

@onready var sp: Node = $SpritePlus
@onready var status: Label = $CanvasLayer/VBox/Status
@onready var btn: Button = $CanvasLayer/VBox/Button

func _ready() -> void:
    # Connect C++ signal and a button
    sp.connect("out_of_bounds", Callable(self, "_on_sprite_plus_out_of_bounds"))
    btn.pressed.connect(_on_button_pressed)

    # Move the sprite across the screen to trigger the signal
    var tw := create_tween()
    tw.tween_property(sp, "position:x", 2500.0, 4.0).set_trans(Tween.TRANS_SINE).set_ease(Tween.EASE_IN_OUT)

func _on_button_pressed() -> void:
    sp.call("external_ping", "ping from Demo.gd")
    status.text = "Status: sent external_ping() (toggled bob)"

func _on_sprite_plus_out_of_bounds(pos: Vector2) -> void:
    status.text = "Status: out_of_bounds at %s" % [pos]
    print("[Demo] SpritePlus out_of_bounds at: ", pos)
