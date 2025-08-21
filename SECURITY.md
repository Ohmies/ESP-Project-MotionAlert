# Security Policy

## Supported Versions

We currently support the following versions of ESP-Project-MotionAlert:

| Version | Supported          |
| ------- | ------------------ |
| 1.x.x   | :white_check_mark: |

## Reporting a Vulnerability

We take security seriously. If you discover a security vulnerability, please follow these steps:

### For Non-Critical Vulnerabilities
- Create an issue on GitHub with the "security" label
- Provide detailed information about the vulnerability
- Include steps to reproduce if applicable

### For Critical Vulnerabilities
- **DO NOT** create a public issue
- Send an email to the project maintainer
- Include detailed information about the vulnerability
- We will respond within 48 hours

## Security Considerations

### LINE API Token Security
- **NEVER** commit your Channel Access Token to version control
- Use environment variables or separate config files (added to .gitignore)
- Regularly rotate your tokens
- Monitor token usage in LINE Developers Console

### WiFi Security
- Use WPA2 or WPA3 encryption for your WiFi network
- Avoid using public WiFi networks for your device
- Consider using a separate IoT network for your devices

### Device Security
- Change default passwords if applicable
- Keep firmware updated
- Use secure boot if available on your ESP32
- Consider implementing OTA (Over-The-Air) updates with signed firmware

### Network Security
- Use HTTPS for all API communications (already implemented)
- Consider implementing certificate pinning for production use
- Monitor network traffic for anomalies

### Code Security
- Validate all inputs
- Use secure coding practices
- Avoid hardcoding sensitive information
- Implement proper error handling

## Best Practices

1. **Token Management**
   - Store tokens in separate files (e.g., `credentials.h`)
   - Add credential files to `.gitignore`
   - Use environment variables when possible

2. **Network Security**
   - Always use HTTPS for API calls
   - Implement proper certificate validation
   - Use secure WiFi networks

3. **Physical Security**
   - Secure physical access to your device
   - Consider tamper detection mechanisms
   - Use enclosures to protect against environmental factors

4. **Update Policy**
   - Keep dependencies updated
   - Monitor security advisories
   - Implement a update mechanism

## Responsible Disclosure

We appreciate security researchers who responsibly disclose vulnerabilities. We commit to:

- Acknowledging receipt of vulnerability reports within 48 hours
- Providing regular updates on remediation progress
- Crediting researchers (if desired) in security advisories
- Working to resolve issues in a timely manner

Thank you for helping keep ESP-Project-MotionAlert secure!
