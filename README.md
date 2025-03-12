# Boggle
## Target Information
Compiler: Visual Studio 2022

Toolset:  v143

Standard: ISO C++17 (/std:c++17)

Target:   Windows x64

## File Structure
```
Boggle/
	design_docs/
		design.pdf
		uml.png
		uml_code.txt
	MaddieBoggle/
		MaddieBoggle.sln
		MaddieBoggle.vcxproj
		includes/
			*.h
		src/
			*.cpp
	MaddieBoggle-Test/
		doubles/
			TestDoubles.h
		tests/
			*_Tests.cpp
	supplementary/
		*.txt
	quick_access/
```
- The `design_docs` directory contains the overall architecture of the application and some design notes with quantitative metrics on how I made decisions to create/improve upon the design.
- The `MaddieBoggle` directory contains the main solution and source files for the application.
- The `MaddieBoggle-Test` directory contains the unit test source files.
- The `supplementary` directory contains several text files used to test the main application.
- The `quick_access` directory contains copies of the application and test executables that I built on my system (in case the solution is unable to be built on another computer). **This directory is NOT where the executables are stored after building.**

## CLI Build Instructions & Deliverables Output

- Ensure `msbuild.exe` is added to your environment variables. Mine was located in `C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin`.
- Navigate to the directory containing the `MaddieBoggle.sln` VS solution - `Boggle\MaddieBoggle\`
- Open a `cmd` windows and run the following command `msbuild MaddieBoggle.sln /p:Configuration=Release`.
- The application executable will be located at `Boggle\MaddieBoggle\x64\Release\BoggleTest.exe`.
- The unit tests executable will be located at `Boggle\MaddieBoggle\x64\Release\BoggleTest-Test.exe`.

## Running the Executables

- After building the solution, navigate to the output build directory `Boggle\MaddieBoggle\x64\Release\`
- Open a `cmd` window.
- Run the application with `BoggleTest <dictionary_filename> <board_filename> <output_filename>`.
- Run the unit tests with `BoggleTest-Test`.
