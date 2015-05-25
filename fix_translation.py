import os
import shutil
from os import walk
from tempfile import mkstemp

# This cript look for all the "index.markdown" files in the english website, and check if all of them are present in each translation directories

translation_directories = ["cn"];
ignored_directories = ["assets", "css"];

# Get the directory where this python script is stored
script_directory = os.path.dirname(os.path.abspath(__file__))
directories = [script_directory]



def remplaceLanguage( file_path, lang ):
    print "remplaceLanguage(%s, %s)" % (file_path, lang)
    markerline = 0;

    #Create temp file
    fh, abs_path = mkstemp()
    print "abs_path %s" % abs_path
    with open(abs_path,"w") as new_file:
        with open(file_path) as old_file:
            for line in old_file:
                if line.startswith("language:"):
                    new_file.write("language: " + lang)
                    new_file.write(os.linesep)
                    markerline = markerline + 1
                elif line.startswith("---") and markerline == 0:
                    new_file.write(line)
                    markerline = markerline + 1
                elif line.startswith("---") and markerline == 1:
                    new_file.write("language: " + lang)
                    new_file.write(os.linesep)
                    new_file.write(line)
                    markerline = markerline + 1
                else:
                    new_file.write(line)
    os.close(fh)
    #Remove original file
    os.remove(file_path)
    #Move new file
    shutil.move(abs_path, file_path)

# 1: We get the list of index.markdown files in the english version of the website
index_markdown_files = []
while len(directories) > 0:
    dir = directories[0]
    # We remove "dir" from the direcotries to be parsed
    directories.remove(dir);
    #print '\n'.join(directories)
    
    # First we get a list of the files and directory to parse present in "dir"
    # And we add them to the directories to parse
    listd = os.listdir(dir)
    for elt in listd:
        if ((not elt.startswith("_"))
            and (not elt in ignored_directories)
            and (not elt.startswith("."))
            and (not elt in translation_directories)
            and (not os.path.isfile(os.path.join(dir,elt)))):
            #print "sub dir %s" % (os.path.join(dir,elt))
            directories.append(os.path.join(dir,elt))
        elif (os.path.isfile(os.path.join(dir,elt))
              and elt == "index.markdown"):
            index_markdown_files.append(os.path.join(dir,elt))

#print "%d index.markdown found" % len(index_markdown_files)

# 2: For each folder in "translation_directories" find if some index.markdown file doesn't exist
for ln in translation_directories:
    missing_index_markdown = []
    for index_file in index_markdown_files:
        f = script_directory
        f = os.path.join(f, ln)
        f = os.path.join(f, index_file[len(script_directory)+1:])
        if not os.path.isfile(f):
            missing_index_markdown.append([f, index_file])
        else:
            remplaceLanguage(f, ln)
    if len(missing_index_markdown) > 0:
        print "Translation %s miss %d index.markdown file" % (ln, len(missing_index_markdown))
        print "Do you want to add them ?"
        answer = raw_input('y / n\n')
        if answer == "y":
            print "Adding files..."
            for mf in missing_index_markdown:
                dirToCreate = os.path.dirname(mf[0])
                if not os.path.exists(dirToCreate):
                    os.makedirs(dirToCreate)
                shutil.copy2(mf[1], mf[0])
                # In the copied file we need to modify the language: xx to language: 'ln'
                remplaceLanguage(mf[0], ln)    

        
