# WTT: Weaknesses Testing Tool
	A Technique to Detect Weaknesses in C Programs
[![MIT License](https://img.shields.io/github/license/xiaocong/uiautomator.svg)](http://opensource.org/licenses/MIT)

## Tool

This repository provides the tool WTT for testing weaknesses in C programs.

### Requirements

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

## Links

- **Website**: building

- **GitHub**: https://github.com/WeaknessesTestingTool/source
