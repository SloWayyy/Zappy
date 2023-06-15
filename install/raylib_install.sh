if [ "$EUID" -ne 0 ]
  then echo "Please run as root"
  exit
fi

echo "Installing RAYLIB for Fedora..."

# Install dependencies
dnf install -y cmake make gcc g++ libX11-devel libXrandr-devel libXcursor-devel libatomic libXi-devel mesa-libGL-devel mesa-libGLU-devel

# Download RAYLIB and unzip
mkdir -p raylib
cd raylib/
wget https://github.com/raysan5/raylib/archive/refs/heads/master.zip
unzip master.zip
cd raylib-master/src

# Install RAYLIB
make PLATFORM=PLATFORM_DESKTOP
make PLATFORM=PLATFORM_DESKTOP RAYLIB_LIBTYPE=SHARED
make install
make install RAYLIB_LIBTYPE=SHARED

# Remove temp files
cd ../../
rm -rf raylib

echo "RAYLIB successfully installed!"
