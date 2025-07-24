echo "Creating build directory..."

mkdir -p build
cd build || { echo "Failed to enter build directory"; exit 1; }

echo "Starting the CMake configuration..."
cmake .. || { echo "CMake configuration failed"; exit 1; }

echo "Building the project..."
make -j$(nproc) || { echo "Build failed"; exit 1; }

echo "Build Completed Successfully!"
