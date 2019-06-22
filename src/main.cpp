#include "hd/Core/hdCommon.hpp"
#include "hd/Core/hdStringUtils.hpp"
#include "hd/System/hdWindow.hpp"
#include "hd/Graphics/hdRenderDevice.hpp"

int main() {
    auto wnd = hd::Window("Cubes", 640, 480);
    auto rnd = hd::RenderDevice(wnd, false, 1);
    auto isExit = false;
    while (!isExit) {
        hd::WindowEvent event;
        while (wnd.processEvent(event)) {
            if (event.type == hd::WindowEventType::Close ||
                (event.type == hd::WindowEventType::Key && event.key.state == hd::KeyState::Released && event.key.code == hd::KeyCode::Escape)) {
                isExit = true;
            }
            if (event.type == hd::WindowEventType::Resize) {
                rnd.resizeBuffers(event.resize.width, event.resize.height);
                rnd.setViewport(0, 0, event.resize.width, event.resize.height);
            }
        }

        rnd.clearRenderTarget(0.5f, 0.5f, 1.0f, 1.0f);
        rnd.clearDepthStencil(1.0f, 0);
        rnd.present();
    }

    return 0;
}