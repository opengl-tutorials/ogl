---
layout: page
title: Translation
author:
  display_name: Sistr
  email: damien.mabin@gmail.com
  url: ''
categories: []
order: 17
tags: []
language: jp
---
{:TOC}

You can help in 2 different ways:

 - Completing and maintaining an already existing translation

 - Adding a completly new translation

Both are really easy to do and require not initial knowlegde of any kind.

## Participating in an already existing translation

Compact version if you're already familliar with GitHub, detailled version below.

> We use the github standard pull-request mechanism.\\
> Fork the repo, and checkout locally the branch "gh-pages" containing this website.\\
> At the root of the repo there is one folder per language other than english (cn for Chinese, fr for French etc).\\
> Traduce/correct all the index.markdown you wish in that folder\\
> Submit your pull request.

More detailed step by step:

 1. Fork the git repository ([GitHub documentation](https://help.github.com/articles/fork-a-repo/) is really complete and clear)
  - Create a GitHub account
  - On GitHub, navigate to [opengl-tutorials](https://github.com/Whiteseeker/opengl-tutorials) repository.
  - In the top-right corner of the page, click Fork.
  
 2. Clone your fork locally ([GitHub documentation](https://help.github.com/articles/fork-a-repo/))
  - Set up Git on your computer ([GiHub documentation](https://help.github.com/articles/set-up-git/) by platform)
  - On [GitHub](https://github.com/) navigate to your fork (bottom right of this link you should have the list of your projects, click on the fork there).
  - In the right sidebar of your repository GitHub page copy the "HTTPS clone URL".
  - Open a console and navigate to a directory where you want to store the tutorial website.
  - Type "git clone -b gh-pages " and paste the url you copy 2 steps earlier "https://github.com/YOUR-USERNAME/opengl-tutorials.git", this will create a directory "opengl-tutorial" in the directory where you run that command line.

 3. If you want to contribute to the page "cn/intermediate-tutorials/tutorial-11-2d-text/" for example, open and edit the "index.markdown" locate in the folder "cn/intermediate-tutorials/tutorial-11-2d-text/".

 4. Commit your modification localy and then submit a pull request by following [GitHub documentation](https://help.github.com/articles/using-pull-requests/).

In case you run in any trouble, don't hesitate the get in touch with us by email [contact@opengl-tutorial.org](mailto:contact@opengl-tutorial.org).

## Adding a completly new translation

Follow step 1 and step 2 of the section above.
Once you have cloned locally your fork, navigate to the root of the repository and locate the folder "translation.zip".
Unzip it and rename it with the 2 letters [iso 639-1](http://en.wikipedia.org/wiki/List_of_ISO_639-1_codes) language code you want to translate (fr for French, es for spanish, etc).
Start traducing every index.markdown in this folder and its subfolder.

Finally follow the step 4 of the section above to submit your pull-request and it'll appear of the website shortly after that.

