import fileinput
import os
import glob
import shutil
from PIL import Image
import subprocess
import sys
import math
from time import sleep

CMakePath = r'C:\Program Files (x86)\CMake\bin\cmake.exe'
VisualStudio10Path = r'C:\Program Files (x86)\Microsoft Visual Studio 10.0\Common7\IDE\devenv.com'
VisualStudio11ExpressPath = r'C:\Program Files (x86)\Microsoft Visual Studio 11.0\Common7\IDE\WDExpress.exe'
VisualStudio14ExpressPath = r'C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\IDE\WDExpress.exe'
CodeBlocksPath = r'C:\Program Files (x86)\CodeBlocks\codeblocks.exe'

def SetCMakePath(path):
	global CMakePath
	CMakePath = path
	
def SetVisualStudio10Path(path):
	global VisualStudio10Path
	CMakePath = path
	
def SetVisualStudio11ExpressPath(path):
	global VisualStudio11ExpressPath
	CMakePath = path

tests = [
	('../tutorial16_shadowmaps/tutorial16_shadowmaps'                 , '../tutorial16_shadowmaps/tutorial16.cpp'               , '../tutorial16_shadowmaps/screenshots/ref.png'                    ),
	('../tutorial14_render_to_texture/tutorial14_render_to_texture'   , '../tutorial14_render_to_texture/tutorial14.cpp'        , '../tutorial14_render_to_texture/screenshots/wavvy.png'           ),
	('../misc05_picking/misc05_picking_slow_easy'                     , '../misc05_picking/misc05_picking_slow_easy.cpp'        , '../misc05_picking/screenshots/ref.png'                           ),
	('../misc05_picking/misc05_picking_custom'                        , '../misc05_picking/misc05_picking_custom.cpp'           , '../misc05_picking/screenshots/ref.png'                           ),
	('../misc05_picking/misc05_picking_BulletPhysics'                 , '../misc05_picking/misc05_picking_BulletPhysics.cpp'    , '../misc05_picking/screenshots/ref.png'                           ),
	('../tutorial09_vbo_indexing/tutorial09_AssImp'                   , '../tutorial09_vbo_indexing/tutorial09_AssImp.cpp'      , '../tutorial09_vbo_indexing/screenshots/ref.png'                  ),
	('../tutorial02_red_triangle/tutorial02_red_triangle'             , '../tutorial02_red_triangle/tutorial02.cpp'             , '../tutorial02_red_triangle/screenshots/red_triangle.png'         ),
	('../tutorial03_matrices/tutorial03_matrices'                     , '../tutorial03_matrices/tutorial03.cpp'                 , '../tutorial03_matrices/screenshots/perspective_red_triangle.png' ),
	('../tutorial04_colored_cube/tutorial04_colored_cube'             , '../tutorial04_colored_cube/tutorial04.cpp'             , '../tutorial04_colored_cube/screenshots/one_color_per_vertex.png' ),
	('../tutorial05_textured_cube/tutorial05_textured_cube'           , '../tutorial05_textured_cube/tutorial05.cpp'            , '../tutorial05_textured_cube/screenshots/textured_cube.png'       ),
	('../tutorial06_keyboard_and_mouse/tutorial06_keyboard_and_mouse' , '../tutorial06_keyboard_and_mouse/tutorial06.cpp'       , '../tutorial06_keyboard_and_mouse/screenshots/ref.png'            ),
	('../tutorial07_model_loading/tutorial07_model_loading'           , '../tutorial07_model_loading/tutorial07.cpp'            , '../tutorial07_model_loading/screenshots/ref.png'                 ),
	('../tutorial08_basic_shading/tutorial08_basic_shading'           , '../tutorial08_basic_shading/tutorial08.cpp'            , '../tutorial08_basic_shading/screenshots/ref.png'                 ),
	('../tutorial09_vbo_indexing/tutorial09_vbo_indexing'             , '../tutorial09_vbo_indexing/tutorial09.cpp'             , '../tutorial09_vbo_indexing/screenshots/ref.png'                  ),
	('../tutorial10_transparency/tutorial10_transparency'             , '../tutorial10_transparency/tutorial10.cpp'             , '../tutorial10_transparency/screenshots/ref.png'                  ),
	('../tutorial11_2d_fonts/tutorial11_2d_fonts'                     , '../tutorial11_2d_fonts/tutorial11.cpp'                 , '../tutorial11_2d_fonts/screenshots/clock.png'                    ),
	('../tutorial13_normal_mapping/tutorial13_normal_mapping'         , '../tutorial13_normal_mapping/tutorial13.cpp'           , '../tutorial13_normal_mapping/screenshots/ref.png'                ),
	('../tutorial15_lightmaps/tutorial15_lightmaps'                   , '../tutorial15_lightmaps/tutorial15.cpp'                , '../tutorial15_lightmaps/screenshots/ref.png'                     ),
	('../tutorial16_shadowmaps/tutorial16_shadowmaps_simple'          , '../tutorial16_shadowmaps/tutorial16_SimpleVersion.cpp' , '../tutorial16_shadowmaps/screenshots/refsimple.png'              ),
	('../tutorial17_rotations/tutorial17_rotations'                   , '../tutorial17_rotations/tutorial17.cpp'                , '../tutorial17_rotations/screenshots/ref.png'                     ),
	('../tutorial18_billboards_and_particles/tutorial18_billboards'   , '../tutorial18_billboards_and_particles/tutorial18_billboards.cpp' , '../tutorial18_billboards_and_particles/screenshots/ref1.png' ),
	('../tutorial18_billboards_and_particles/tutorial18_particles'    , '../tutorial18_billboards_and_particles/tutorial18_particles.cpp'  , '../tutorial18_billboards_and_particles/screenshots/ref2.png' )
]

def RemoveDirs(paths):
	for path in paths:	
		shutil.rmtree(path, False)

def RemoveFiles(paths):
	for path in paths:	
		if os.path.exists(path): os.remove(path)
	
def Clean():

	if "noclean" in sys.argv:
		return

	dirs = glob.glob('./build_*');
	exes = [];
	if os.name == 'nt':
		exes = glob.glob('../tutorial*/*.exe');
	else:
		exes = glob.glob('../tutorial*/*');
		exes = [exe for exe in exes if os.access(exe, os.X_OK) and not os.path.isdir(exe)]
	RemoveDirs(dirs);
	RemoveFiles(exes);


def InsertScreenshotCode(path):
	for line in fileinput.input(path, inplace = 1): # Does a list of files, and writes redirects STDOUT to the file in question
		print line.replace("#include <glfw3.h>", "#include <glfw3.h>\n#include \"distrib/screenshot.h\" // added by insertscreenshot.py; should NOT be committed !"),
	  
def __HgUpdate21():
	os.system('hg update --clean "2.1 branch"')

def GitUpdate21():
	os.system('git checkout -f origin/2.1_branch')
	
def __HgUpdate33():
	os.system('hg update --clean "default"')
	
def GitUpdate33():
	os.system('git checkout -f origin/master')

	
def Build_VC10_32():
	print "Building with Visual Studio 10, 32 bits"
	global CMakePath
	global VisualStudio10Path
	if os.path.exists("build_VC10_32") == False: 
		os.makedirs("build_VC10_32")
	os.chdir("build_VC10_32")
	with open(os.devnull, "w") as fnull:
		print "Running CMake..."
		subprocess.call( [CMakePath, '-G', 'Visual Studio 10', '-D', 'INCLUDE_DISTRIB:bool=true', '../../'], stdout=fnull, stderr=fnull )
		print "Compiling everything..."
		subprocess.call( [VisualStudio10Path, '/build', 'RelWithDebInfo', 'Tutorials.sln'], stdout=fnull, stderr=fnull )
	os.chdir("..")

def Build_VC10_64():
	print "Building with Visual Studio 10, 64 bits"
	global CMakePath
	global VisualStudio10Path
	if os.path.exists("build_VC10_64") == False: 
		os.makedirs("build_VC10_64")
	os.chdir("build_VC10_64")
	with open(os.devnull, "w") as fnull:
		print "Running CMake..."
		subprocess.call( [CMakePath, '-G', 'Visual Studio 10 Win64', '-D', 'INCLUDE_DISTRIB:bool=true', '../../'], stdout=fnull, stderr=fnull )
		print "Compiling everything..."
		subprocess.call( [VisualStudio10Path, '/build', 'RelWithDebInfo', 'Tutorials.sln'], stdout=fnull, stderr=fnull )
	os.chdir("..")

	
def Build_VC11Express_32():
	print "Building with Visual Studio 12 Express Desktop, 32 bits"
	global CMakePath
	global VisualStudio11ExpressPath
	if os.path.exists("build_VC11_32") == False: 
		os.makedirs("build_VC11_32")
	os.chdir("build_VC11_32")
	with open(os.devnull, "w") as fnull:
		print "Running CMake..."
		subprocess.call( [CMakePath, '-G', 'Visual Studio 11', '-D', 'INCLUDE_DISTRIB:bool=true', '../../'], stdout=fnull, stderr=fnull )
		print "Compiling everything..."
		subprocess.call( [VisualStudio11ExpressPath, '/build', 'RelWithDebInfo', 'Tutorials.sln'], stdout=fnull, stderr=fnull )
	os.chdir("..")

def Build_VC11Express_64():
	print "Building with Visual Studio 11 Express Desktop, 64 bits"
	global CMakePath
	global VisualStudio11ExpressPath
	if os.path.exists("build_VC11_64") == False: 
		os.makedirs("build_VC11_64")
	os.chdir("build_VC11_64")
	with open(os.devnull, "w") as fnull:
		print "Running CMake..."
		subprocess.call( [CMakePath, '-G', 'Visual Studio 11 Win64', '-D', 'INCLUDE_DISTRIB:bool=true', '../../'], stdout=fnull, stderr=fnull )
		print "Compiling everything..."
		subprocess.call( [VisualStudio11ExpressPath, '/build', 'RelWithDebInfo', 'Tutorials.sln'], stdout=fnull, stderr=fnull )
	os.chdir("..")

	
def Build_VC14Express_32():
	print "Building with Visual Studio 14 Express Desktop, 32 bits"
	global CMakePath
	global VisualStudio14ExpressPath
	if os.path.exists("build_VC14_32") == False: 
		os.makedirs("build_VC14_32")
	os.chdir("build_VC14_32")
	with open(os.devnull, "w") as fnull:
		print "Running CMake..."
		subprocess.call( [CMakePath, '-G', 'Visual Studio 14', '-D', 'INCLUDE_DISTRIB:bool=true', '../../'], stdout=fnull, stderr=fnull )
		print "Compiling everything..."
		subprocess.call( [VisualStudio14ExpressPath, '/build', 'RelWithDebInfo', 'Tutorials.sln'], stdout=fnull, stderr=fnull )
	os.chdir("..")

def Build_VC14Express_64():
	print "Building with Visual Studio 14 Express Desktop, 64 bits"
	global CMakePath
	global VisualStudio14ExpressPath
	if os.path.exists("build_VC14_64") == False: 
		os.makedirs("build_VC14_64")
	os.chdir("build_VC14_64")
	with open(os.devnull, "w") as fnull:
		print "Running CMake..."
		subprocess.call( [CMakePath, '-G', 'Visual Studio 14 Win64', '-D', 'INCLUDE_DISTRIB:bool=true', '../../'], stdout=fnull, stderr=fnull )
		print "Compiling everything..."
		subprocess.call( [VisualStudio14ExpressPath, '/build', 'RelWithDebInfo', 'Tutorials.sln'], stdout=fnull, stderr=fnull )
	os.chdir("..")


	
def Build_CodeBlocks():
	print "Building with Code::Blocks, ?? bits"
	global CMakePath
	global CodeBlocksPath
	if os.path.exists("build_CodeBlocks") == False: 
		os.makedirs("build_CodeBlocks")
	os.chdir("build_CodeBlocks")
	if os.path.exists("codeblocks.log"):
		os.remove("codeblocks.log")
	with open(os.devnull, "w") as fnull:
		print "Running CMake..."
		subprocess.call( [CMakePath, '-G', 'CodeBlocks - MinGW Makefiles', '-D', 'INCLUDE_DISTRIB:bool=true', '../../'], stdout=fnull, stderr=fnull )
		print "Compiling everything..."
		subprocess.call( [CodeBlocksPath, '--build', '--target=all', '--log-to-file', 'Tutorials.cbp'], stdout=fnull, stderr=fnull )
		while not os.path.exists("codeblocks.log"):
			sleep(0.5) # Not started yet
		while not "No tasks" in subprocess.check_output( ['tasklist', '/FI', 'IMAGENAME eq codeblocks.exe'], stderr=fnull ):
			sleep(0.5) # Still running
	if os.path.exists("tutorial01_first_window.exe") == False:
		print "This exceeds theshold ! Go fix your code."
		raise Exception()
	os.chdir("..")
	
def Build_GCC_native():
	print "Building with GCC, ?? bits"
	global CMakePath
	if os.path.exists("build_GCC") == False: 
		os.makedirs("build_GCC")
	os.chdir("build_GCC")
	with open(os.devnull, "w") as fnull:
		print "Running CMake..."
		subprocess.call( ['cmake', '-G', 'Visual Studio 10 Win64', '-D', 'INCLUDE_DISTRIB:bool=true', '../../'], stdout=fnull, stderr=fnull )
		print "Compiling everything..."
		subprocess.call( ['make', '-j4'], stdout=fnull, stderr=fnull )
	os.chdir("..")

def Build_XCode_64():
	print "Building with XCode, 64 bits"
	global CMakePath
	if os.path.exists("build_XCode_64") == False: 
		os.makedirs("build_XCode_64")
	os.chdir("build_XCode_64")
	with open(os.devnull, "w") as fnull:
		print "Running CMake..."
		subprocess.call( ['cmake', '-G', 'Xcode', '-D', 'INCLUDE_DISTRIB:bool=true', '../../'], stdout=fnull, stderr=fnull )
		print "Compiling everything..."
		subprocess.call( ['xcodebuild', '-configuration', 'RelWithDebInfo', '-arch', 'x86_64'], stdout=fnull, stderr=fnull )
	os.chdir("..")
	
def PatchAll():
	for test in tests:
		InsertScreenshotCode(test[1])

def Compare(dir, test):
	print "Comparing " + dir + "/screenshot.bmp" + " and " + test[2] + "..."
	
	if os.path.exists(dir + "/screenshot.bmp") == False: print "No screenshot was generated !"
	if os.path.exists(test[2]                ) == False: print "Reference image does not exist !"
	
	generated = Image.open(dir + "/screenshot.bmp")
	reference = Image.open(test[2])

	if generated.size != reference.size or generated.getbands() != reference.getbands():
		return -1
		
	h1 = generated.histogram()
	h2 = reference.histogram()

	diff_squares = [(h1[i] - h2[i]) ** 2 for i in xrange(len(h1))];
	rms = math.sqrt(sum(diff_squares) / len(h1));
	#rms = math.sqrt(reduce(operator.add,map(lambda a,b: (a-b)**2, h1, h2))/len(h1))

	print "Difference : " + str(rms)
	if rms > 100*1000:
		print "This exceeds theshold ! Go fix your code."
		raise Exception()

		
def RunAll():
	cwd = os.getcwd()

	for test in tests:
		path = test[0]
		if os.name == 'nt' : 
			path += '.exe'
		dir = path.split('/')
		dir.pop()
		dir = '/'.join(dir)
		print "Running " + path.split('/').pop() + " from "+ dir;
		os.chdir(dir);
		RemoveFiles([dir + "/screenshot.bmp"])
		with open(os.devnull, "w") as fnull:
			subprocess.call(path, stdout=fnull, stderr=fnull)
		os.chdir(cwd);
		Compare(dir, test)

	os.chdir(cwd);

def AcceptAll():
	cwd = os.getcwd()

	for test in tests:
		path = test[0]
		if os.name == 'nt' : 
			path += '.exe'
		dir = path.split('/')
		dir.pop()
		dir = '/'.join(dir)
		print "Running " + path.split('/').pop() + " from "+ dir;
		os.chdir(dir);
		with open(os.devnull, "w") as fnull:
			subprocess.call(path, stdout=fnull, stderr=fnull)
		os.chdir(cwd);
		Image.open(dir + "/screenshot.bmp").save(test[2])

	os.chdir(cwd);
	
def OptimusForceIntel():
	print "Forcing Intel GPU (on Optimus system)..."
	subprocess.call(["selectoptimus.exe", "INTEL"])
	
def OptimusForceNVIDIA():
	print "Forcing NVidia GPU (on Optimus system)..."
	subprocess.call(["selectoptimus.exe", "NVIDIA"])

def __Package(path):
	print "Packaging into " + path + " ..."
	cwd = os.getcwd()
	os.chdir("..");
	os.system('hg archive --exclude .hg* --exclude distrib* '+path)
	os.chdir(cwd);
	
	
if "simplerun" in sys.argv:
	RunAll()
	exit()
	
#AcceptAll()
	
# Clean()

# HgUpdate21()
# PatchAll()
# Build_VC10_32()
# OptimusForceIntel()
# RunAll()
# OptimusForceNVIDIA()
# RunAll()

# Clean()

# HgUpdate33()
# PatchAll()
# Build_VC10_32()
# OptimusForceNVIDIA()
# RunAll()

# Clean()

# Build_CodeBlocks()

#Clean()
