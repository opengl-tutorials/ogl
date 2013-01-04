import fileinput
import os
import glob
import shutil
from PIL import Image
#import numpy
import subprocess
import sys

CMakePath = r'C:\Program Files (x86)\CMake 2.8\bin\cmake.exe'
VisualStudio10Path = r'C:\Program Files (x86)\Microsoft Visual Studio 10.0\Common7\IDE\devenv.com'

def SetCMakePath(path):
	global CMakePath
	CMakePath = path
	
def SetVisualStudio10Path(path):
	global VisualStudio10Path
	CMakePath = path

tests = [
	('../tutorial16_shadowmaps/tutorial16_shadowmaps'                 , '../tutorial16_shadowmaps/tutorial16.cpp'               , '../tutorial16_shadowmaps/screenshots/ref.png'                    ),
	('../tutorial14_render_to_texture/tutorial14_render_to_texture'   , '../tutorial14_render_to_texture/tutorial14.cpp'        , '../tutorial14_render_to_texture/screenshots/wavvy.png'           ),
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
	#('../tutorial13_normal_mapping/tutorial13_normal_mapping'         , '../tutorial13_normal_mapping/tutorial13.cpp'           , '../tutorial13_normal_mapping/screenshots/ref.png'               ),
	('../tutorial15_lightmaps/tutorial15_lightmaps'                   , '../tutorial15_lightmaps/tutorial15.cpp'                , '../tutorial15_lightmaps/screenshots/ref.png'                     ),
	('../tutorial16_shadowmaps/tutorial16_shadowmaps_simple'          , '../tutorial16_shadowmaps/tutorial16_SimpleVersion.cpp' , '../tutorial16_shadowmaps/screenshots/refsimple.png'              ),
	#('../tutorial17_rotations/tutorial17_rotations'                   , '../tutorial17_rotations/tutorial17.cpp'                , '../tutorial17_rotations/screenshots/ref.png'                    )
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
		exes = [exe for exe in exes if os.access(exe, os.X_OK)]
	RemoveDirs(dirs);
	RemoveFiles(exes);


def InsertScreenshotCode(path):
	for line in fileinput.input(path, inplace = 1): # Does a list of files, and writes redirects STDOUT to the file in question
		print line.replace("#include <GL/glfw.h>", "#include <GL/glfw.h>\n#include \"distrib/screenshot.h\" // added by insertscreenshot.py; should NOT be committed !"),
	  
def HgUpdate21():
	os.system('hg update --clean "2.1 branch"')

def HgUpdate33():
	os.system('hg update --clean "default"')
	
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

	s = 0
	for band_index, band in enumerate(generated.getbands()):
		m1 = numpy.array([p[band_index] for p in generated.getdata()]).reshape(*generated.size)
		m2 = numpy.array([p[band_index] for p in reference.getdata()]).reshape(*reference.size)
		s += numpy.sum(numpy.abs(m1-m2))
	print "Difference : " + str(s)
	if s > 100*1000:
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

def Package(path):
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

#Clean()
