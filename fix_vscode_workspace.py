import os
import json

if not os.path.exists(".vscode"):
    os.makedirs(".vscode")

data = {
    "C_Cpp.default.includePath": [
        "include",
        "lib/CrossPlatformDataBus",
        "lib/MPU",
        "lib/WiringPi"
    ],
    "files.exclude": {
        ".vscode": True,
        ".gitignore": True,
        "lib": True,
        "*.sh": False,
        "*.py": False,
        "*.md": False
    },
    "editor.minimap.enabled": False
}

with open(".vscode/settings.json", "w") as write_file:
    json.dump(data, write_file, indent=4)
