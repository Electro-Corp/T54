cd src
cd chead
git clone https://sourceware.org/git/glibc.git
cd glibc
git checkout master
cd ~
cd T54
find src/chead/glibc -type f -print0 | xargs -0 mv -t src/chead
