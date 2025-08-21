#!/bin/bash

# setup.sh - Setup script for ESP-Project-MotionAlert
# This script helps you set up the project for development

echo "🚀 ESP-Project-MotionAlert Setup Script"
echo "======================================"

# Check if PlatformIO is installed
if ! command -v pio &> /dev/null; then
    echo "❌ PlatformIO CLI not found. Please install PlatformIO first."
    echo "   Visit: https://platformio.org/install/cli"
    exit 1
fi

echo "✅ PlatformIO CLI found"

# Create credentials file if it doesn't exist
if [ ! -f "include/credentials.h" ]; then
    echo "📝 Creating credentials.h from template..."
    cp include/credentials.h.example include/credentials.h
    echo "⚠️  Please edit include/credentials.h with your actual credentials"
else
    echo "✅ credentials.h already exists"
fi

# Install dependencies
echo "📦 Installing project dependencies..."
pio lib install

# Build the project
echo "🔨 Building project..."
if pio run; then
    echo "✅ Build successful!"
else
    echo "❌ Build failed. Please check errors above."
    exit 1
fi

echo ""
echo "🎉 Setup complete!"
echo ""
echo "Next steps:"
echo "1. Edit include/credentials.h with your WiFi and LINE API credentials"
echo "2. Connect your ESP32 and PIR sensor according to CIRCUIT.md"
echo "3. Upload the code: pio run --target upload"
echo "4. Monitor serial output: pio device monitor"
echo ""
echo "📚 Read README.md for detailed instructions"
