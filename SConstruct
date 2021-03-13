env = Environment()

env.Append(LIBS = ["user32", "Gdi32"])
env.Append(CFLAGS = "/I src/ /DEBUG")

dirs = [
    "gui/platform/windows"
]

files = Glob("src/*.c")

for d in dirs:
    files += Glob("src/" + d + "/*.c")

env.Program("Calc", files)
