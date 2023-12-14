#%%
import os, os.path

#%%
diretorio_atual = os.getcwd()

#%%
for root, _, files in os.walk(diretorio_atual):
    for f in files:
        fullpath = os.path.join(root, f)
        if '.git' not in fullpath:
            if os.path.getsize(fullpath) > 48000 * 1024:
                print(fullpath)
                os.remove(fullpath)
# %%
