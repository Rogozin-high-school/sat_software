import os
import json

if not os.path.exists(".vscode"):
    os.makedirs(".vscode")

data = {
    "C_Cpp.default.includePath": [
        "include",
        "include/subsystems"
    ],
    "C_Cpp.default.defines": [
        "LOGGING"
    ],
    "C_Cpp.default.forcedInclude": [
        "include/logger.hpp"
    ],
    "files.exclude": {
        ".vscode": False,
        ".gitignore": False,
        "lib": False,
        "*.sh": False,
        "*.py": False,
        "*.md": False
    },
    "editor.minimap.enabled": False
}

with open(".vscode/settings.json", "w") as write_file:
    json.dump(data, write_file, indent=4)
