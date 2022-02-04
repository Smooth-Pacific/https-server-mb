# Creator:   VPR
# Created:   February 3, 2022
# Updated:   February 3, 2022

set -e pipefail
set -e errexit
set -e nounset
set -e xtrace

PASSWORD="abcdefg"
COUNTRY_NAME="US"
STATE="STATE"
LOCALE="CITY"
ORGANIZATION="ORGANIZATION"
ORGANIZATION_UNIT="UNIT"
COMMON_NAME="SS" # Smooth Stack
EMAIL="email@example.com"

# Install open-ssl if not already installed
if [ $(dpkg-query -W -f='${Status}' openssl 2>/dev/null | grep -c "ok installed") -eq 0 ];
then
  apt-get install openssl;
fi

# House certificates in home directory
mkdir -p ~/certs
cd ~/certs

# Generate private key
openssl genrsa -des3 -passout pass:${PASSWORD} -out local-CA.key 4096

# Generate root certificate
echo "${COUNTRY_NAME}\n${STATE}\n${LOCALE}\n${ORGANIZATION}\n${ORGANIZATION_UNIT}\n${COMMON_NAME}\n${EMAIL}\n" | \
openssl req -x509 -new -nodes -key local-CA.key -sha256 -passin pass:${PASSWORD} -days 365 -out root-CA.pem

# Change OS CA to match newly created CA
# TODO
