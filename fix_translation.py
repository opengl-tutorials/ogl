import os
import shutil
import re
from os import walk
from tempfile import mkstemp

# This cript look for all the "index.markdown" files in the english website, and check if all of them are present in each translation directories

translation_directories = ["cn", "jp", "ru", "es"];
ignored_directories = ["assets", "css"];

# Get the directory where this python script is stored
script_directory = os.path.dirname(os.path.abspath(__file__))
directories = [script_directory]

def getOrder( file_path ):
    order = -1;
    #Create temp file
    with open(file_path) as en_file:
        for line in en_file:
            if line.startswith("order:"):
                matchObj = re.search( r'[0-9]+', line, re.M|re.I )
                order = int(matchObj.group(0))
                break

    return order


def remplaceLanguage( file_path, lang, order ):
    #print "remplaceLanguage(%s, %s, %d)" % (file_path, lang, order)
    # headerState store if we have write the language line or not
    # 0 : mean we haven't read "---" yet
    # 1 : mean we read "---" but haven't leaved the header yet (we are in th header)
    # 2 : mean we read "---" for the second time, we are out of the header
    headerState = 0;

    # languageState store if we have write the language line or not
    # 0 : mean we haven't read or write the language line
    # 1 : mean the language line has been written
    languageState = 0;

    orderState = 0;

    #Create temp file
    fh, abs_path = mkstemp()    
    with open(abs_path,"w") as new_file:
        with open(file_path) as old_file:
            for line in old_file:
                # If we found the language line we set the right value for it
                if line.startswith("language:") and headerState == 1:
                    new_file.write("language: " + lang)
                    new_file.write(os.linesep)
                    languageState = 1
                elif line.startswith("order:") and order >= 0 and headerState == 1:
                    new_file.write("order: " + str(order))
                    new_file.write(os.linesep)
                    orderState = 1
                elif line.startswith("---") and headerState == 0:
                    new_file.write(line)
                    headerState = 1
                # If we are going to close the liquid header, we first write the language line if necessaru
                elif line.startswith("---") and headerState == 1:
                    if languageState == 0:
                        new_file.write("language: " + lang)
                        new_file.write(os.linesep)
                        languageState = 1
                    if orderState == 0 and order >= 0:
                        new_file.write("order: " + str(order))
                        new_file.write(os.linesep)
                        orderState = 1
                    headerState = 2
                    new_file.write(line)
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
    # We remove "dir" from the directories to be parsed
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
    print "Checking %s translation" % ln
    missing_index_markdown = []
    for index_file in index_markdown_files:
        f = script_directory
        f = os.path.join(f, ln)
        f = os.path.join(f, index_file[len(script_directory)+1:])
        if not os.path.isfile(f):
            missing_index_markdown.append([f, index_file])
        else:
            order = getOrder(index_file)
            remplaceLanguage(f, ln, order)
    if len(missing_index_markdown) > 0:
        print "Translation %s miss %d index.markdown file" % (ln, len(missing_index_markdown))
        for mf in missing_index_markdown:
            print "missing: %s" % mf[0]
        print "Do you want to add them ?"
        answer = raw_input('y / n\n')
        if answer == "y":
            print "Adding files..."
            for mf in missing_index_markdown:
                dirToCreate = os.path.dirname(mf[0])
                if not os.path.exists(dirToCreate):
                    os.makedirs(dirToCreate)
                shutil.copy2(mf[1], mf[0])
                order = getOrder(mf[1])
                # In the copied file we need to modify the language: xx to language: 'ln'
                remplaceLanguage(mf[0], ln, order)    

        
