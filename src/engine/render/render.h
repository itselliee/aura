//
// Created by ellie on 7/28/26.
//

#include "../generalImports.h"

namespace Aura {
    class Renderer {
        public:

        void Render() {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
        }

        private:
    };
}