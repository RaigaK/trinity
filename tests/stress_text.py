import sys
sys.path.append("../../../../packages")
import binbootstrapper
binbootstrapper.update_binaries(__file__, *binbootstrapper.DLLS_GRAPHICS)

import random
import blue
import trinity
from windowsutilities.windowsEvents import *
import ctypes

class POINT(ctypes.Structure):
    _fields_ = [('x', ctypes.c_long),
                ('y', ctypes.c_long)]

class MSG(ctypes.Structure):
    _fields_ = [('hwnd', ctypes.c_int),
                ('message', ctypes.c_uint),
                ('wParam', ctypes.c_int),
                ('lParam', ctypes.c_int),
                ('time', ctypes.c_int),
                ('pt', POINT)]

EXAMPLE_TEXT = """
Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.
"""

SHADER_MODELS = ["SM_3_0_LO", "SM_3_0_HI", "SM_3_0_DEPTH"]


class MyApp(object):
    def __init__(self):
        blue.paths.SetSearchPath("resCarbon", u"../../../../carbon/client/res")
        blue.paths.SetSearchPath("resLocal", u"../../../../eve/client/res")
        blue.paths.SetSearchPath("res", u"resLocal:;resCarbon:")

    def OnAppEvent(self, msgID, wParam, lParam):
        returnValue = 0

        if msgID == WM_CLOSE:
            blue.os.Terminate()

        elif msgID == WM_ERASEBKGND:
            returnValue = 0

        else:
            returnValue = None

        return returnValue
        

    def SetupDevice(self):
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

        trinity.app.ChangeDevice(0, 0, 0, pp)


    def MainLoop(self):
        msg = MSG()
        pMsg = ctypes.pointer(msg)
        running = True
        TranslateMessage = ctypes.windll.user32.TranslateMessage
        DispatchMessageA = ctypes.windll.user32.DispatchMessageA
        PeekMessageA = ctypes.windll.user32.PeekMessageA

        while running:
            while PeekMessageA( pMsg, 0, 0, 0, 1):
                if msg.message == WM_QUIT:
                    running = False
                    break
                TranslateMessage(pMsg)
                DispatchMessageA(pMsg)

            self.Update()
            blue.os.Pump()


    def AddContainers(self, spriteObj, depth):
        for i in xrange(10):
            cont = trinity.Tr2Sprite2dContainer()
            if random.random() < 0.2:
                cont.cacheContents = True
            cont.displayWidth = trinity.app.width
            cont.displayHeight = trinity.app.height
            self.containers.append(cont)
            spriteObj.children.append(cont)
            depth -= 1
            if depth > 0:
                self.AddContainers(cont, depth)

    def AddText(self):
        sprite = trinity.Tr2Sprite2dTextObject()
        sprite.color = (1, 1, 1, 1)
        self.ChangeText(sprite)
        self.containers[random.randrange(len(self.containers))].children.append(sprite)
        self.textObjects.append(sprite)

    def ChangeText(self, sprite):
        n = len(EXAMPLE_TEXT)
        fm = trinity.Tr2FontMeasurer()
        fm.font = "res:/UI/Fonts/EveSansNeue-Regular.otf"
        fm.fontSize = random.randint(8, 36)
        start = random.randrange(n)
        end = start + random.randrange(n/2)
        text = EXAMPLE_TEXT[start:end]
        if random.random() < 0.05:
            fm.underline = True

        fm.AddText(text)
        fm.CommitText(0, fm.ascender)

        sprite.fontMeasurer = fm
        sprite.displayX = random.randrange(trinity.app.width)
        sprite.displayY = random.randrange(trinity.app.height)
        sprite.textWidth = fm.cursorX
        sprite.textHeight = fm.ascender - fm.descender

    def Update(self):
        pass

    def UpdateChangingText(self):
        sprite = self.textObjects[random.randrange(len(self.textObjects))]
        self.ChangeText(sprite)

        if random.random() < 0.01:
            pp = {
                "BackBufferWidth": 800 + random.randrange(100),
                "BackBufferHeight": 600 + random.randrange(100),
                "Windowed": True,
                "EnableAutoDepthStencil": True,
                "AutoDepthStencilFormat": trinity.DEPTH_STENCIL_FORMAT.D24S8
            }
            try:
                trinity.app.ChangeDevice(0, 0, 0, pp)
            except:
                pass

        elif random.random() < 0.01:
            trinity.SetShaderModel(SHADER_MODELS[random.randrange(len(SHADER_MODELS))])

    def SetupTextInContainers(self):
        self.containers = []
        self.textObjects = []
        self.AddContainers(self.spriteScene, 10)
        for i in xrange(1000):
            self.AddText()

        self.Update = self.UpdateChangingText

    def SetupLongText(self, numLines, numCharsPerLine):
        fm = trinity.Tr2FontMeasurer()
        fm.font = "res:/UI/Fonts/EveSansNeue-Regular.otf"
        fm.fontSize = 12
        width = 0
        y = 0

        words = EXAMPLE_TEXT.split(" ")
        numWords = len(words)
        for lineIx in xrange(numLines):
            line = ""
            while(len(line) < numCharsPerLine):
                line += words[random.randrange(numWords)]
                if len(line) < numCharsPerLine:
                    line += " "
            fm.AddText(line)
            if y == 0:
                y = fm.ascender
            fm.CommitText(0, y)
            y += fm.ascender
            if fm.cursorX > width:
                width = fm.cursorX
            fm.cursorX = 0

        sprite = trinity.Tr2Sprite2dTextObject()
        sprite.color = (1, 1, 1, 1)
        sprite.fontMeasurer = fm
        sprite.textWidth = width
        sprite.textHeight = y

        self.spriteScene.children.append(sprite)

    def Run(self):
        self.SetupDevice()

        self.spriteScene = trinity.Tr2Sprite2dScene()
        self.spriteScene.displayWidth = trinity.app.width
        self.spriteScene.displayHeight = trinity.app.height

        #self.SetupTextInContainers()
        self.SetupLongText(20, 100)

        self.renderJob = trinity.CreateRenderJob("SpriteRenderJob")
        self.renderJob.Update(self.spriteScene)
        self.renderJob.Clear((0,0,0,1), 1)
        self.renderJob.RenderScene(self.spriteScene)
        self.renderJob.RenderFps()

        self.renderJob.ScheduleRecurring()

        trinity.app.eventHandler = self.OnAppEvent
        self.MainLoop()

app = MyApp()
app.Run()
