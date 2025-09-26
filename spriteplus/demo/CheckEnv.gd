extends Node2D

func _ready() -> void:
    print("CheckEnv: project launched OK (no GDExtension required).")
    var label := Label.new()
    label.text = "CheckEnv: project launched OK (no GDExtension)."
    label.position = Vector2(20, 20)
    add_child(label)
