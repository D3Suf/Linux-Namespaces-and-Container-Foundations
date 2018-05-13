# Linux-Namespaces-and-Container-Foundations
Sprint 4 - Linux Namespaces and Container Foundations

# Review Docker
Some Docker commands:

```
docker build -t newphytonimage .            # Create image using this directory's Dockerfile
docker run -p 8080:80 newphytonimage        # Run "newphytonimage" mapping port 8080 to 80
docker run -d -p 8080:80 newphytonimage     # Same but in detached mode
```

# Linux Namespaces

```
UTS (Unix Timesharing System): hostname / uname
IPC: inter-process communication
PID: "chroot" process tree
NS: mount points
NET: network access, including interfaces
USER: map virtual, local user-ids to real local ones
```