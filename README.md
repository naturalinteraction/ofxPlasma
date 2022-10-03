ofxPlasma
=========

An openFrameworks addon to integrate Oblong Industries' Plasma. Tested on Ubuntu 20.04.

This addon lives here: `https://github.com/naturalinteraction/ofxPlasma.git`

The included license is that of Plasma. You can freely use ofxPlasma as you wish.

The easiest way to learn how to use this addon is to look at the included `/example`.

This has been put together by me (Alessandro Valli, naturalinteract at gmail.com) and has nothing to do with Oblong Industries, Inc.

# What is Plasma?

Plasma is an open-source system for platform- and language-independent data
encapsulation and transmission.

It can be found here: `https://github.com/Oblong/plasma`

Arbitrarily complex -- in the senses of aggregation and nesting -- data
structures are represented by objects called 'Slawx' (the plural of 'Slaw')
and, when intended for cross-process relay, by elaborated Slawx called
'Proteins'. Slawx and Proteins are schemaless but self-describing, meaning
that a recipient can interrogate any of these objects to discover its
structure, the component data types at each sublocation, and of course the
data itself.

A process deposits Proteins into, and retrieves Proteins from, network-soluble
ring buffers called 'Pools'. Multiple processes can be simultaneously
connected (via 'Hoses') to a single pool, with each both depoisiting and
retrieving Proteins. The ordering of Proteins stored in a Pool is monotonic
and immutable, such that all retrieving processes observe the same
sequence. Processes most typically read from Pools in something like real
time, with Proteins being retrieved immediately after being deposited; but
Pools are also 'rewindable' so that, for example, a new process joining a
distributed system might attach to a Pool already in use and begin reading
Proteins from a time far enough in the past to be able to reconstruct system
context.

The Plasma framework embodies a philosophy of system design that appeals to an
endocrinology (rather than telegraphy) metaphor. The name 'Plasma' accordingly
refers not to the superheated, ionized stellar substance but rather to the
liquid medium by which biological organisms' messaging molecules are
transported and diffused.

# building the thing

(see up-to-date instructions in the plasma repository)

Building Plasma requires:

- ninja
- cmake
- libyaml
- boost
- icu4c
- openssl

Use your package manager (brew, apt, yum, zypper, etc) to install them.

To build on linux/intel mac, assuming you're in the same directory as this README:

- `sudo apt-get install libavahi-client-dev libavahi-core-dev`
- `mkdir build`
- `cd build`
- `cmake -GNinja ..`
- `ninja`
- `sudo ninja install` will create `/include` and `/share`

Support
-------------------------------
- Tested on Ubuntu 20.04.5 LTS + openFrameworks 0.11.2-master
