import unittest
import trinity
import blue
import sys
import tempfile
import shutil

def SetupDeviceIfNeeded():
    if trinity.app.hwnd:
        return

    trinity.SetShaderModel('SM_3_0_DEPTH')
    trinity.device.tickInterval = 0 

    w = 900
    h = 500

    trinity.app.width = w
    trinity.app.height = h
    trinity.app.left = 100
    trinity.app.top = 100
    trinity.app.Create()

    pp = {
        "BackBufferWidth": w,
        "BackBufferHeight": h,
        "Windowed": True,
        "EnableAutoDepthStencil": True,
        "AutoDepthStencilFormat": trinity.DEPTH_STENCIL_FORMAT.D24S8
    }

    adapter = trinity.adapters.GetAdapterInfo(0)
    trinity.app.ChangeDevice(0, 0, 0, pp)


class TestTrinity(unittest.TestCase):
    """
    A set of test cases for TestTrinity.
    """
    def setUp(self):
        SetupDeviceIfNeeded()

    def test_CreateRenderTargets(self):
        rt1 = trinity.Tr2RenderTarget(256, 128, 1, trinity.PIXEL_FORMAT.B8G8R8A8_UNORM, trinity.TRIMULTISAMPLE_8_SAMPLES, 2)
        rt2 = trinity.Tr2RenderTarget(256, 128, 0, trinity.PIXEL_FORMAT.B8G8R8A8_UNORM)

        self.assertTrue(    rt1.isValid, 
                            'failed to create a MSAA renderTarget')
        self.assertTrue(    rt2.isValid, 
                            'failed to create a non-MSAA renderTarget')

        self.assertTrue(    rt1.multiSampleType    == trinity.TRIMULTISAMPLE_8_SAMPLES,
                            'constructor did not read the MSAA samplecount correctly')
        self.assertTrue(    rt1.multiSampleQuality == 2,
                            'constructor did not read the MSAA quality correctly')
        self.assertTrue(    rt1.mipCount           == 1,
                            'constructor did not read the mipcount correctly')

        self.assertTrue(    rt2.multiSampleType    == 1,
                            'constructor did not read the MSAA samplecount correctly')
        self.assertTrue(    rt2.multiSampleQuality == 0,
                            'constructor did not read the MSAA quality correctly')
        self.assertTrue(    rt2.mipCount           == 0,
                            'constructor did not read the mipcount correctly')

class TestSprite2dScene(unittest.TestCase):
    """
    A set of test cases for Tr2Sprite2dScene and related classes
    """

    def setUp(self):
        SetupDeviceIfNeeded()
        trinity.textureAtlasMan.AddAtlas(trinity.PIXEL_FORMAT.B8G8R8A8_UNORM, 1024, 1024)
        self.atlas = trinity.textureAtlasMan.atlases[0]


    def tearDown(self):
        self.atlas = None
        trinity.textureAtlasMan.RemoveAtlas(trinity.PIXEL_FORMAT.B8G8R8A8_UNORM)


    def test_1(self):
        scene = trinity.Tr2Sprite2dScene()