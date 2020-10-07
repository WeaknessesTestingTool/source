# WTT: Weaknesses Testing Tool
	A Technique to Detect Weaknesses in C Programs
[![MIT License](https://img.shields.io/github/license/xiaocong/uiautomator.svg)](http://opensource.org/licenses/MIT)

### This repository provides the tool WTT for testing weaknesses in C programs.

### Requirements

#### Tools
- Flawfinder version ?
- AFL version ?
- CMocka ?

Firstly, system core dumps must be disabled as with AFL.

```sh
$ echo core|sudo tee /proc/sys/kernel/core_pattern
$ echo performance|sudo tee /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor
```

### Clone the Repository

```sh
$ git clone https://github.com/WeaknessesTestingTool/source.git WTT
$ cd WTT
```
Instrument the main.sh file as the example presented in the File folder.

## Links

- **Website**: https://weaknessestestingtool.github.io/wtt/

- **GitHub**: https://github.com/WeaknessesTestingTool/source

## Author
 -

## License
	WTT is available under the MIT license. See the LICENSE file for more info.
