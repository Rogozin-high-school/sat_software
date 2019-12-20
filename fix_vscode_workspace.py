import os
import json

if not os.path.exists(".vscode"):
    os.makedirs(".vscode")

data = {
    "C_Cpp.default.includePath": [
        "include"
    ],
    "C_Cpp.default.defines": [
        "log(...)=printf(__VA_ARGS__)"
        # "log(...)"
    ],
    "files.exclude": {
        ".vscode": True,
        ".gitignore": True,
        "lib": False,
        "*.sh": False,
        "*.py": False,
        "*.md": False
    },
    "editor.minimap.enabled": False
}

with open(".vscode/settings.json", "w") as write_file:
    json.dump(data, write_file, indent=4)
