set -e  # Exit on error

echo "Checking Prerequisites..."
echo ""

# Array to track packages to install
PACKAGES_TO_INSTALL=()

# Check for g++
echo "Checking for g++..."
if command -v g++ &> /dev/null; then
    echo "g++ found: $(g++ --version | head -n1)"
else
    echo "g++ not found - will install"
    PACKAGES_TO_INSTALL+=("g++")
fi
echo ""

# Check for make
echo "Checking for make..."
if command -v make &> /dev/null; then
    echo "make found: $(make --version | head -n1)"
else
    echo "make not found - will install"
    PACKAGES_TO_INSTALL+=("make")
fi
echo ""

# Check for cmake
echo "Checking for cmake..."
if command -v cmake &> /dev/null; then
    echo "cmake found: $(cmake --version | head -n1)"
else
    echo "cmake not found - will install"
    PACKAGES_TO_INSTALL+=("cmake")
fi
echo ""

# Check for git
echo "Checking for git..."
if command -v git &> /dev/null; then
    echo "git found: $(git --version)"
else
    echo "git not found - will install"
    PACKAGES_TO_INSTALL+=("git")
fi
echo ""

# Install missing packages if any
if [ ${#PACKAGES_TO_INSTALL[@]} -gt 0 ]; then
    echo "Installing Missing Prerequisites..."
    echo "Packages to install: ${PACKAGES_TO_INSTALL[*]}"
    echo ""
    
    # Check if we can use sudo
    if command -v sudo &> /dev/null; then
        echo "Updating package list..."
        sudo apt-get update -qq
        echo ""
        echo "Installing packages..."
        sudo apt-get install -y "${PACKAGES_TO_INSTALL[@]}"
        echo ""
        echo "All missing packages installed successfully!"
    else
        echo "ERROR: sudo not available. Please install manually:"
        echo " apt-get install ${PACKAGES_TO_INSTALL[*]}"
        exit 1
    fi
    echo ""
fi

# Check for qmake (Qt) 
echo "Checking for qmake (Qt)..."
if command -v qmake &> /dev/null; then
    echo "qmake found: $(qmake --version | head -n1)"
else
    echo "qmake not found - will install"
    PACKAGES_TO_INSTALL+=("qt5-qmake" "qtbase5-dev")
    
fi
echo ""
echo ""
echo "Setting up Google Test..."
echo ""

# Clone Google Test if not already present
if [ ! -d "extern/googletest/.git" ]; then
    echo "Google Test not found. Cloning repository..."
    mkdir -p extern/googletest
    git clone https://github.com/google/googletest.git extern/googletest
    echo "Google Test cloned successfully"
else
    echo "Google Test already cloned"
fi
echo ""

# Build Google Test if not already built
if [ ! -f "extern/googletest/build/lib/libgtest.a" ]; then
    echo "Building Google Test..."
    mkdir -p extern/googletest/build
    cd extern/googletest/build
    cmake ..
    make
    cd ../../..
    echo "Google Test built successfully"
else
    echo "Google Test already built"
fi
echo ""

echo "Setup Complete!"
echo ""
echo "All prerequisites are installed and Google Test is ready."

