# Uploading Old Project: YouTube to MP3 Converter (C++)

This is an old project I worked on to build a simple **YouTube to MP3 Converter** using C++.  
The application allows users to **fetch video metadata and convert YouTube videos to MP3 files** using `yt-dlp` and `ffmpeg`.

---

## Dependencies
To run this project, you need the following dependencies installed:

1. **C++ Compiler** (`g++` or `clang++`)
2. **curl** (For fetching YouTube HTML data)
   - Install via Homebrew: `brew install curl`
3. **yt-dlp** (For downloading YouTube audio)
   - Install via Homebrew: `brew install yt-dlp`
   - Or via pip: `pip install yt-dlp`
4. **ffmpeg** (For converting audio to MP3)
   - Install via Homebrew: `brew install ffmpeg`
5. **nlohmann/json** (For parsing JSON data)
   - Download from: [https://github.com/nlohmann/json](https://github.com/nlohmann/json)
   - Place the `json.hpp` file in a folder named `nlohmann` in the project directory.

---

