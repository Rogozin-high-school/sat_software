import os
import json

if not os.path.exists(".vscode"):
    os.makedirs(".vscode")

data = {
    "C_Cpp.default.includePath": [
        "include"
    ],
    "C_Cpp.default.defines": [
        "LOGGING",
        "LOGGING_FUNCTION_CALLS",
        "PROPERTIES_FILE=\"properties\""
    ],
    "C_Cpp.default.forcedInclude": [
        "include/Logger.hpp"
    ],
    "files.exclude": {
        "satellite": True,
        ".vscode": True,
        ".gitignore": True,
        "lib": False,
        "*.sh": False,
        "*.py": False,
        "*.md": False
    }
}

with open(".vscode/settings.json", "w") as write_file:
    json.dump(data, write_file, indent=4)
