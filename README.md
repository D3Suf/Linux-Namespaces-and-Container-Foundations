# Linux-Namespaces-and-Container-Foundations
Sprint 4 - Linux Namespaces and Container Foundations

# Review Docker
Some Docker commands:

```
docker build -t newphytonimage .            # Create image using this directory's Dockerfile
docker run -p 8080:80 newphytonimage        # Run "newphytonimage" mapping port 8080 to 80
docker run -d -p 8080:80 newphytonimage     # Same but in detached mode
```