TEMPLATE = subdirs

SUBDIRS += \
    MeshToolbox \
    OpenMesh
MeshToolbox.depends = OpenMesh
