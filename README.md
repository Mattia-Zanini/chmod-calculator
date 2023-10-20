# chmod-calculator

There are various things to consider; just for completeness:

First of all, you should make sure that this executable has in fact the required permissions.

'''shell
sudo chmod a+rx /path/to/profit
'''

(for example when extracting archives that were thrown together using the zip tool, permissions can get lost)

Then you can either copy the file as Gunnar suggested; or you can create a symbolic link:

'''shell
sudo ln -s /path/to/profit /usr/local/bin
'''
Depending on your context, using a link might be more convenient in the future; on the other hand it carries some security risks (for example when /path/to/profit can be written by non-root users)
