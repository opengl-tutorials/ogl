from utils import *
	
HgUpdate33()
version = raw_input("Enter version number (ex : 0003) :")
Package("OpenGL-tutorial_v"+version+"_33.zip");
HgUpdate21()
Package("OpenGL-tutorial_v"+version+"_21.zip");
HgUpdate33()
