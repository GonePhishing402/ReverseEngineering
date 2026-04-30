# Dynamic Analysis

Dynamic analysis involves executing a program in a controlled environment and observing its behavior at runtime — network calls, file system activity, registry changes, and more.

## Directory Structure

```
DynamicAnalysis/
├── FakeNet/
│   ├── FakeNet_Walkthrough.md
│   └── demofile.c
├── Images/
└── README.md
```

## Tools

### [FakeNet-NG](FakeNet/FakeNet_Walkthrough.md)
FakeNet-NG is a dynamic network analysis tool that intercepts and simulates network traffic, allowing you to observe what domains, IPs, and protocols a suspicious binary communicates with — without it ever reaching the internet.

- [Walkthrough](FakeNet/FakeNet_Walkthrough.md)
- [Demo sample (demofile.c)](FakeNet/demofile.c)
- [Official GitHub Repository](https://github.com/mandiant/flare-fakenet-ng)
- [Official Documentation](https://github.com/mandiant/flare-fakenet-ng/blob/master/docs/README.md)
