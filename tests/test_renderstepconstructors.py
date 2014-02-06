import unittest
import trinity
import blue

import test_trinity

class TestRenderStepConstructors(unittest.TestCase):
    """
    A set of test cases for render step creation. This is primarily intended
    for regression testing render steps while converting constructors to use
    new Blue exposure.
    """
    def setUp(self):
        test_trinity.SetupDeviceIfNeeded()
        
    def test_TriStepClear(self):
        #CONV: Optional args won't work - can't distinguish null values from legit values
        step = trinity.TriStepClear()
        self.assertFalse(step.isColorCleared)
        self.assertFalse(step.isDepthCleared)
        self.assertFalse(step.isStencilCleared)

        # Color without alpha
        colorWithoutAlpha = (0,0,0)
        colorWithAlpha = (0,0,0,1)
        step = trinity.TriStepClear(colorWithoutAlpha)
        self.assertTrue(step.isColorCleared)
        self.assertFalse(step.isDepthCleared)
        self.assertFalse(step.isStencilCleared)
        self.assertEqual(step.color, colorWithAlpha)

        # Color with alpha
        step = trinity.TriStepClear(colorWithAlpha)
        self.assertTrue(step.isColorCleared)
        self.assertFalse(step.isDepthCleared)
        self.assertFalse(step.isStencilCleared)
        self.assertEqual(step.color, colorWithAlpha)

        depth = 1.0
        step = trinity.TriStepClear(colorWithAlpha, depth)
        self.assertTrue(step.isColorCleared)
        self.assertTrue(step.isDepthCleared)
        self.assertFalse(step.isStencilCleared)
        self.assertEqual(step.color, colorWithAlpha)
        self.assertAlmostEqual(step.depth, depth, 6)

        stencil = 0
        step = trinity.TriStepClear(colorWithAlpha, depth, stencil)
        self.assertTrue(step.isColorCleared)
        self.assertTrue(step.isDepthCleared)
        self.assertTrue(step.isStencilCleared)
        self.assertEqual(step.color, colorWithAlpha)
        self.assertAlmostEqual(step.depth, depth, 6)
        self.assertEqual(step.stencil, stencil)

        # Fail cases
        # Too many args
        self.assertRaises(TypeError, trinity.TriStepClear, colorWithAlpha, depth, stencil, 0)

        # Wrong type
        self.assertRaises(TypeError, trinity.TriStepClear, 0, depth, stencil)
        self.assertRaises(TypeError, trinity.TriStepClear, colorWithAlpha, "depth", stencil)
        self.assertRaises(TypeError, trinity.TriStepClear, colorWithAlpha, depth, "stencil")


    def test_TriStepClearUav(self):
        # CONV: Optional args won't work - can't deal with float/int tuple
        step = trinity.TriStepClearUav()
        self.assertEqual(step.buffer, None)

        buffer = trinity.Tr2GpuBuffer()
        step = trinity.TriStepClearUav(buffer)
        self.assertEqual(step.buffer, buffer)

        values = (0,3,18,326784)
        step = trinity.TriStepClearUav(buffer, values)
        self.assertEqual(step.buffer, buffer)
        self.assertFalse(step.clearWithFloat)
        self.assertEqual(step.bitValue0, values[0])
        self.assertEqual(step.bitValue1, values[1])
        self.assertEqual(step.bitValue2, values[2])
        self.assertEqual(step.bitValue3, values[3])

        values = (3.14, 0.47, 13.12341234, -345134.315098)
        step = trinity.TriStepClearUav(buffer, values)
        self.assertEqual(step.buffer, buffer)
        self.assertTrue(step.clearWithFloat)

        # Checking the float value is tricky as Python works with double precision.
        # These values were converted to single precision floats when set. Ignoring
        # this for now.

        # Fail cases
        # Too many args
        self.assertRaises(TypeError, trinity.TriStepClearUav, buffer, values, 0)

        # Wrong type
        self.assertRaises(TypeError, trinity.TriStepClearUav, 0, values)
        self.assertRaises(TypeError, trinity.TriStepClearUav, buffer, 0)


    def test_TriStepCopyRenderTarget(self):
        # CONV: Optional args won't work - arg types are overloaded
        pass


    def test_TriStepEnableWireframeMode(self):
        # CONV: Done!

        step = trinity.TriStepEnableWireframeMode()
        self.assertFalse(step.enableWireframe)

        step = trinity.TriStepEnableWireframeMode(False)
        self.assertFalse(step.enableWireframe)
        
        step = trinity.TriStepEnableWireframeMode(True)
        self.assertTrue(step.enableWireframe)

        # Fail cases
        # Too many args
        self.assertRaises(TypeError, trinity.TriStepEnableWireframeMode, True, 0)

        # Wrong type
        self.assertRaises(TypeError, trinity.TriStepEnableWireframeMode, "True")
        self.assertRaises(TypeError, trinity.TriStepEnableWireframeMode, 3.14)


    def test_TriStepFilterVisibilityResults(self):
        #CONV: Optional args won't work - can't distinguish null values from legit values

        step = trinity.TriStepFilterVisibilityResults()
        self.assertEqual(step.eventFilter, -1)
        self.assertEqual(step.filterType, 1)

        #TODO: fill in the rest
        
    def test_TriStepGenerateMipMaps(self):
        # CONV: Done!

        step = trinity.TriStepGenerateMipMaps()
        self.assertEqual(step.renderTarget, None)

        renderTarget = trinity.Tr2RenderTarget()
        step = trinity.TriStepGenerateMipMaps(renderTarget)
        self.assertEqual(step.renderTarget, renderTarget)

        self.assertRaises(TypeError, trinity.TriStepGenerateMipMaps, 42)

        
    def test_TriStepPopDepthStencil(self):
        # CONV: No constructor
        
        step = trinity.TriStepPopDepthStencil()

        #self.assertRaises(TypeError, trinity.TriStepPopDepthStencil, 42)

        
    def test_TriStepPopProjection(self):
        # CONV: No constructor

        step = trinity.TriStepPopProjection()

        #self.assertRaises(TypeError, trinity.TriStepPopProjection, 42)

        
    def test_TriStepPopRenderTarget(self):
        # CONV: No constructor

        step = trinity.TriStepPopRenderTarget()

        #self.assertRaises(TypeError, trinity.TriStepPopRenderTarget, 42)

       
    def test_TriStepPopViewport(self):
        # CONV: No constructor

        step = trinity.TriStepPopViewport()

        #self.assertRaises(TypeError, trinity.TriStepPopViewport, 42)

        
    def test_TriStepPopViewTransform(self):
        # CONV: No constructor

        step = trinity.TriStepPopViewTransform()

        #self.assertRaises(TypeError, trinity.TriStepPopViewTransform, 42)

        
    def test_TriStepPresentSwapChain(self):
        # CONV: Done!

        step = trinity.TriStepPresentSwapChain()
        self.assertEqual(step.swapChain, None)

        step = trinity.TriStepPresentSwapChain(None)
        self.assertEqual(step.swapChain, None)

        swapChain = trinity.Tr2SwapChain()
        step = trinity.TriStepPresentSwapChain(swapChain)
        self.assertEqual(step.swapChain, swapChain)

        self.assertRaises(TypeError, trinity.TriStepPresentSwapChain, swapChain, 42)
        self.assertRaises(TypeError, trinity.TriStepPresentSwapChain, 42)

        
    def test_TriStepPushDepthStencil(self):
        #CONV: Optional args won't work - passing in None is different from no args

        step = trinity.TriStepPushDepthStencil()
        self.assertEqual(step.depthStencil, None)
        self.assertTrue(step.pushCurrent)

        step = trinity.TriStepPushDepthStencil(None)
        self.assertEqual(step.depthStencil, None)
        self.assertFalse(step.pushCurrent)

        depthStencil = trinity.Tr2DepthStencil()
        step = trinity.TriStepPushDepthStencil(depthStencil)
        self.assertEqual(step.depthStencil, depthStencil)
        self.assertFalse(step.pushCurrent)

        self.assertRaises(TypeError, trinity.TriStepPushDepthStencil, depthStencil, 42)
        #self.assertRaises(TypeError, trinity.TriStepPushDepthStencil, 42)

        
    def test_TriStepPushProjection(self):
        # CONV: No constructor

        step = trinity.TriStepPushProjection()

        #self.assertRaises(TypeError, trinity.TriStepPushProjection, 42)

        
    def test_TriStepPushRenderTarget(self):
        # CONV: Done!

        step = trinity.TriStepPushRenderTarget()
        self.assertEqual(step.renderTarget, None)

        step = trinity.TriStepPushRenderTarget(None)
        self.assertEqual(step.renderTarget, None)

        renderTarget = trinity.Tr2RenderTarget()
        step = trinity.TriStepPushRenderTarget(renderTarget)
        self.assertEqual(step.renderTarget, renderTarget)

        self.assertRaises(TypeError, trinity.TriStepPushRenderTarget, renderTarget, 42)
        self.assertRaises(TypeError, trinity.TriStepPushRenderTarget, 42)


        
    def test_TriStepPushViewport(self):
        # CONV: No constructor

        step = trinity.TriStepPushViewport()

        #self.assertRaises(TypeError, trinity.TriStepPushViewport, 42)

        
    def test_TriStepPushViewTransform(self):
        # CONV: No constructor

        step = trinity.TriStepPushViewTransform()

        #self.assertRaises(TypeError, trinity.TriStepPushViewTransform, 42)

        
    def test_TriStepPythonCB(self):
        # There is no way of verifying the state
        step = trinity.TriStepPythonCB()
        step = trinity.TriStepPythonCB(None)

        def DummyCallback():
            pass

        step = trinity.TriStepPythonCB(DummyCallback)
        
        # This should fail:
        # step = trinity.TriStepPythonCB(42)

        
    def test_TriStepRemoteSync(self):
        # There is no way of verifying the state
        # CONV: Default value is -1 - optional args won't work
        # No checking is done of result of PyArg_ParseTuple
        step = trinity.TriStepRemoteSync()
        step = trinity.TriStepRemoteSync(0)

        #self.assertRaises(TypeError, trinity.TriStepRemoteSync, 0, 42)
        #self.assertRaises(TypeError, trinity.TriStepRemoteSync, None)

        
    def test_TriStepRemoteUpdate(self):
        # There is no way of verifying the state
        # No checking is done of result of PyArg_ParseTuple
        pass

        
    def test_TriStepRenderAtlas(self):
        # CONV: can be done - class needs a bit of cleanup, need testing of that before converting constructor
        step = trinity.TriStepRenderAtlas()
        self.assertEqual(step.atlas, None)
        self.assertEqual(step.focus, None)

        atlas = trinity.Tr2TextureAtlas()
        step = trinity.TriStepRenderAtlas(atlas)
        self.assertEqual(step.atlas, atlas)
        self.assertEqual(step.focus, None)

        focus = trinity.Tr2AtlasTexture()
        step = trinity.TriStepRenderAtlas(atlas, focus)
        self.assertEqual(step.atlas, atlas)
        self.assertEqual(step.focus, focus)

        # The C++ constructor tries to read in an effect from a file. That fails
        # and sets an error that leaks in here.
        #self.assertRaises(TypeError, trinity.TriStepRenderAtlas, atlas, focus, 0)
        #self.assertRaises(TypeError, trinity.TriStepRenderAtlas, 0)
        #self.assertRaises(TypeError, trinity.TriStepRenderAtlas, 0, 0)
        #self.assertRaises(TypeError, trinity.TriStepRenderAtlas, atlas, 0)
        
    
    def test_TriStepRenderCubeMap(self):
        # CONV: Done!

        step = trinity.TriStepRenderCubeMap()
        self.assertEqual(step.texture, None)

        step = trinity.TriStepRenderCubeMap(None)
        self.assertEqual(step.texture, None)

        texture = trinity.TriTextureRes()
        step = trinity.TriStepRenderCubeMap(texture)
        self.assertEqual(step.texture, texture)

        self.assertRaises(TypeError, trinity.TriStepRenderCubeMap, texture, 0)
        self.assertRaises(TypeError, trinity.TriStepRenderCubeMap, 0)

        
    def test_TriStepRenderDebug(self):
        # CONV: No constructor

        step = trinity.TriStepRenderDebug()

        #self.assertRaises(TypeError, trinity.TriStepRenderDebug, 42)


    def test_TriStepRenderEffect(self):
        # CONV: Done!

        step = trinity.TriStepRenderEffect()
        self.assertEqual(step.effect, None)

        step = trinity.TriStepRenderEffect(None)
        self.assertEqual(step.effect, None)

        effect = trinity.Tr2Effect()
        step = trinity.TriStepRenderEffect(effect)
        self.assertEqual(step.effect, effect)

        self.assertRaises(TypeError, trinity.TriStepRenderEffect, effect, 0)
        self.assertRaises(TypeError, trinity.TriStepRenderEffect, 0)

         
    def test_TriStepRenderFps(self):
        # CONV: No constructor

        step = trinity.TriStepRenderFps()

        #self.assertRaises(TypeError, trinity.TriStepRenderFps, 42)

        
    def test_TriStepRenderFullScreenShader(self):
        # CONV: Done!

        step = trinity.TriStepRenderFullScreenShader()
        self.assertEqual(step.shader, None)

        step = trinity.TriStepRenderFullScreenShader(None)
        self.assertEqual(step.shader, None)

        shader = trinity.Tr2ShaderMaterial()
        step = trinity.TriStepRenderFullScreenShader(shader)
        self.assertEqual(step.shader, shader)

        self.assertRaises(TypeError, trinity.TriStepRenderFullScreenShader, shader, 0)
        self.assertRaises(TypeError, trinity.TriStepRenderFullScreenShader, 0)

        
    def test_TriStepRenderLineGraph(self):
        # CONV: Optional args won't work - defaults are not null values
        pass

        
    def test_TriStepRenderObject(self):
        # CONV: Done!

        step = trinity.TriStepRenderObject()
        self.assertEqual(step.renderable, None)

        step = trinity.TriStepRenderObject(None)
        self.assertEqual(step.renderable, None)

        renderable = trinity.EveShip2()
        step = trinity.TriStepRenderObject(renderable)
        self.assertEqual(step.renderable, renderable)

        self.assertRaises(TypeError, trinity.TriStepRenderObject, renderable, 0)
        self.assertRaises(TypeError, trinity.TriStepRenderObject, 0)

        
    def test_TriStepRenderPass(self):
        # CONV: Done!

        step = trinity.TriStepRenderPass()
        self.assertEqual(step.scene, None)
        self.assertEqual(step.passType, 0)

        scene = trinity.EveSpaceScene()
        step = trinity.TriStepRenderPass(scene)
        self.assertEqual(step.scene, scene)
        self.assertEqual(step.passType, 0)

        scene = trinity.EveSpaceScene()
        passType = trinity.TRIPASS_LIGHT_PASS
        step = trinity.TriStepRenderPass(scene, passType)
        self.assertEqual(step.scene, scene)
        self.assertEqual(step.passType, passType)

        self.assertRaises(TypeError, trinity.TriStepRenderPass, scene, passType, 0)
        self.assertRaises(TypeError, trinity.TriStepRenderPass, 0, passType)
        self.assertRaises(TypeError, trinity.TriStepRenderPass, scene, "bla")

        
    def test_TriStepRenderScene(self):
        # CONV: Done!

        step = trinity.TriStepRenderScene()
        self.assertEqual(step.scene, None)

        step = trinity.TriStepRenderScene(None)
        self.assertEqual(step.scene, None)

        scene = trinity.EveSpaceScene()
        step = trinity.TriStepRenderScene(scene)
        self.assertEqual(step.scene, scene)

        self.assertRaises(TypeError, trinity.TriStepRenderScene, scene, 0)
        self.assertRaises(TypeError, trinity.TriStepRenderScene, 0)

        
    def test_TriStepRenderSceneDebug(self):
        # CONV: Done!

        step = trinity.TriStepRenderSceneDebug()
        self.assertEqual(step.scene, None)

        step = trinity.TriStepRenderSceneDebug(None)
        self.assertEqual(step.scene, None)

        scene = trinity.EveSpaceScene()
        step = trinity.TriStepRenderSceneDebug(scene)
        self.assertEqual(step.scene, scene)

        self.assertRaises(TypeError, trinity.TriStepRenderSceneDebug, scene, 0)
        self.assertRaises(TypeError, trinity.TriStepRenderSceneDebug, 0)

        
    def test_TriStepRenderTexture(self):
        # Constructor accepts multiple types
        pass

        
    def test_TriStepResolve(self):
        destination = trinity.Tr2RenderTarget()
        source = trinity.Tr2RenderTarget()

        step = trinity.TriStepResolve(destination, source)
        self.assertEqual(step.destination, destination)
        self.assertEqual(step.source, source)

        self.assertRaises(TypeError, trinity.TriStepResolve)
        self.assertRaises(TypeError, trinity.TriStepResolve, 0)
        self.assertRaises(TypeError, trinity.TriStepResolve, 0, 0)

        
    def test_TriStepRunComputeShader(self):
        pass

        
    def test_TriStepRunJob(self):
        pass

        
    def test_TriStepSetDebugRenderer(self):
        pass

        
    def test_TriStepSetDepthStencil(self):
        pass

        
    def test_TriStepSetProjection(self):
        pass

        
    def test_TriStepSetRenderState(self):
        pass

        
    def test_TriStepSetRenderTarget(self):
        pass

        
    def test_TriStepSetStandardRenderStates(self):
        pass

        
    def test_TriStepSetVariableStore(self):
        pass

        
    def test_TriStepSetVisibilityResults(self):
        pass

        
    def test_TriStepSetVisualizationMode(self):
        pass

        
    def test_TriStepTestBlocking(self):
        pass

        
    def test_TriStepToggleCubemap(self):
        pass

        
    def test_TriStepUpdate(self):
        pass

        
    def test_TriStepVisibilityQuery(self):
        pass

