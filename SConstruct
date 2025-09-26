from SCons.Script import *
import os

env = DefaultEnvironment()
env.Replace(CXX="clang++")

PROJECT_ROOT = Dir('..').abspath
GODOT_CPP_INCLUDE      = os.path.join(PROJECT_ROOT, 'godot-cpp', 'include')
GODOT_CPP_GEN_INCLUDE  = os.path.join(PROJECT_ROOT, 'godot-cpp', 'gen', 'include')
GODOT_HEADERS_GDEXT    = os.path.join(PROJECT_ROOT, 'godot-cpp', 'gdextension')
GODOT_CPP_LIBDIR       = os.path.join(PROJECT_ROOT, 'godot-cpp', 'bin')

platform = ARGUMENTS.get('platform', 'macos')            # windows|linux|macos
target   = ARGUMENTS.get('target',   'template_debug')   # template_debug|template_release

# Absolute paths to the static libs you built (universal)
GODOT_CPP_LIB_DEBUG   = os.path.join(GODOT_CPP_LIBDIR, 'libgodot-cpp.macos.template_debug.universal.a')
GODOT_CPP_LIB_RELEASE = os.path.join(GODOT_CPP_LIBDIR, 'libgodot-cpp.macos.template_release.universal.a')
GODOT_CPP_LIB = GODOT_CPP_LIB_DEBUG if target == 'template_debug' else GODOT_CPP_LIB_RELEASE

env.Append(CPPPATH=[GODOT_CPP_INCLUDE, GODOT_CPP_GEN_INCLUDE, GODOT_HEADERS_GDEXT])
env.Append(LIBPATH=[GODOT_CPP_LIBDIR])
env.Append(CXXFLAGS=['-std=c++17','-fPIC'])

# macOS linker: pull ALL objects from the static lib (fixes missing symbol at runtime)
if platform == 'macos':
    env.Append(LINKFLAGS=['-Wl,-undefined,dynamic_lookup', '-Wl,-force_load', GODOT_CPP_LIB])
    lib_ext = '.dylib'
elif platform == 'linux':
    lib_ext = '.so'
else:
    lib_ext = '.dll'

out_dir = 'addons/sprite_plus/bin'
env.Command(out_dir, [], Mkdir(out_dir))

sources = Glob('src/*.cpp')

# Remove 'lib' prefix so filenames match .gdextension entries
env['SHLIBPREFIX'] = ''

env.SharedLibrary(
    target = os.path.join(out_dir, f'sprite_plus.{platform}.{target}'),
    source = sources,
    SHLIBSUFFIX = lib_ext
)
