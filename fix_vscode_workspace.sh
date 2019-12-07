python3 << END
import os
import json

if not os.path.exists(".vscode"):
    os.makedirs(".vscode")

data = {
    "configurations": [
        {
            "name": "Linux",
            "includePath": [
                "include",
                "lib"
            ]
        }
    ],
    "version": 4
}

with open(".vscode/c_cpp_properties.json", "w") as write_file:
    json.dump(data, write_file, indent=4)

data = {
    "files.exclude": {
        ".vscode": True,
        ".gitignore": True,
        ".directory": True,
        "*.md": True,
        "bin": True,
	"lib": True,
        "res": True,
        "*.sh": True,
        "*.py": True
    },
    "editor.minimap.enabled": False
}

with open(".vscode/settings.json", "w") as write_file:
    json.dump(data, write_file, indent=4)
END
