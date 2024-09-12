unique_addressesBzip = set()

with open("bzip.trace", 'r') as bzipFile:
    for line in bzipFile:
        address, _ = line.strip().split()

        unique_addressesBzip.add(address)

numAddressesBzip = len(unique_addressesBzip)

print("bZip: " + str(numAddressesBzip))
#print(unique_addressesBzip)

unique_addressesGCC = set()

with open("gcc.trace", 'r') as gccFile:
    for line in gccFile:
        address, _ = line.strip().split()

        unique_addressesGCC.add(address)

numAddressesGCC = len(unique_addressesGCC)

print("GCC: " + str(numAddressesGCC))


unique_addressesSwim = set()

with open("swim.trace", 'r') as swimFile:
    for line in swimFile:
        address, _ = line.strip().split()

        unique_addressesSwim.add(address)

numAddressesSwim = len(unique_addressesSwim)

print("Swim: " + str(numAddressesSwim))


unique_addressesSixpack = set()

with open("sixpack.trace", 'r') as sixpackFile:
    for line in sixpackFile:
        address, _ = line.strip().split()

        unique_addressesSixpack.add(address)

numAddressesSixpack = len(unique_addressesSixpack)

print("Sixpack: " + str(numAddressesSixpack))