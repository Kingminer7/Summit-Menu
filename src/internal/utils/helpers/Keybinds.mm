#ifdef GEODE_IS_MACOS

/*
Thanks very much SpaghettDev
https://github.com/SpaghettDev/BetterInputs/blob/master/src/macos.mm
*/

#include "utils/KeybindManager.hpp"
#include <AppKit/NSEvent.h>
#define CommentType CommentTypeDummy
#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#undef CommentType

#include <Carbon/Carbon.h>
#import <objc/runtime.h>

#include <Geode/modify/CCTouchDispatcher.hpp>
#include <Geode/cocos/platform/mac/CCEventDispatcher.h>
#import <Geode/cocos/platform/mac/EAGLView.h>

namespace summit::keybinds {
    inline bool keyDown(summit::keybinds::Keys key, NSEvent* event) {
        switch (key)
        {
            case summit::keybinds::Keys::LeftControl:
				return [event modifierFlags] & NSEventModifierFlagCommand;
            case summit::keybinds::Keys::LeftShift:
                return [event modifierFlags] & NSEventModifierFlagShift;
            case summit::keybinds::Keys::LeftAlt:
                return [event modifierFlags] & NSEventModifierFlagOption;
            case summit::keybinds::Keys::LeftSuper:
                return [event modifierFlags] & NSEventModifierFlagControl;
            default:
                return false;
        }
    }

		inline summit::keybinds::Keys getKey(NSEvent *event) {
			int code = [[event characters] length] > 0
						? [[event characters] characterAtIndex:0]
						: [[event charactersIgnoringModifiers] length] > 0
							? [[event charactersIgnoringModifiers] characterAtIndex:0]
							: 0;
		}
}

#define HOOK_OBJC_METHOD(klass, type, cleanFuncName, funcName) \
	do { \
		auto cleanFuncName ## Method = class_getInstanceMethod(objc_getClass(#klass), @selector(funcName)); \
		cleanFuncName ## OIMP = reinterpret_cast<type>(method_getImplementation(cleanFuncName ## Method)); \
		method_setImplementation(cleanFuncName ## Method, reinterpret_cast<IMP>(&cleanFuncName)); \
		geode::log::debug("Hooked Objective C Method '" #klass " " #funcName "'"); \
	} while(0)

using key_event_t = void(*)(EAGLView*, SEL, NSEvent*);

static key_event_t keyDownExecOIMP;
void keyDownExec(EAGLView* self, SEL sel, NSEvent* event)
{
    int modifiers = (summit::keybinds::keyDown(summit::keybinds::Keys::LeftSuper, event) ? 1 : 0)
        + (summit::keybinds::keyDown(summit::keybinds::Keys::LeftShift, event) ? 2 : 0)
        + (summit::keybinds::keyDown(summit::keybinds::Keys::LeftAlt, event) ? 4 : 0)
        + (summit::keybinds::keyDown(summit::keybinds::Keys::LeftControl, event) ? 8 : 0);

		if (summit::keybinds::KeybindManager::get()->checkBinds(summit::keybinds::Keys::Unknown, summit::keybinds::KeyStates::Press, modifiers)) return;

	// switch ([event keyCode])
	// {
	// 	case kVK_RightArrow:
	// 		return g_selectedInput->onRightArrowKey(
	// 			BI::platform::keyDown(BI::PlatformKey::LEFT_ALT, event),
	// 			BI::platform::keyDown(BI::PlatformKey::LEFT_SHIFT, event)
	// 		);

	// 	case kVK_LeftArrow:
	// 		return g_selectedInput->onLeftArrowKey(
	// 			BI::platform::keyDown(BI::PlatformKey::LEFT_ALT, event),
	// 			BI::platform::keyDown(BI::PlatformKey::LEFT_SHIFT, event)
	// 		);

	// 	default:
	// 		break;
	// }

	// if (
	// 	![event isARepeat] &&
	// 	BI::platform::keyDown(BI::PlatformKey::LEFT_CONTROL, event) &&
	// 	!BI::platform::keyDown(BI::PlatformKey::LEFT_SHIFT, event)
	// ) {
	// 	// https://github.com/WebKit/WebKit/blob/5c8281f146cfbf4b6189b435b80c527f138b829f/Source/WebCore/platform/mac/PlatformEventFactoryMac.mm#L559
	// 	// we use this instead of [event keyCode] because the returned value of keyCode for letters is keyboard locale-specific

	// 	switch ([event keyCode])
	// 	{
	// 		case kVK_Delete:
	// 		case kVK_ForwardDelete:
	// 			g_selectedInput->onDelete(true, [event keyCode] == kVK_ForwardDelete);
	// 			break;

	// 		default:
	// 			break;
	// 	}

	// 	switch (code)
	// 	{
	// 		case 'a': case 'A':
	// 			return g_selectedInput->highlightFromToPos(0, -1);

	// 		case 'c': case 'C':
	// 			return g_selectedInput->onCopy();

	// 		case 'v': case 'V':
	// 			return g_selectedInput->onPaste();

	// 		case 'x': case 'X':
	// 			return g_selectedInput->onCut();

	// 		default:
	// 			break;
	// 	}
	// }

	// if (![event isARepeat])
	// {
	// 	if (!BI::platform::keyDown(BI::PlatformKey::LEFT_CONTROL, event))
	// 	{
	// 		switch ([event keyCode])
	// 		{
	// 			case kVK_Home:
	// 				return g_selectedInput->onHomeKey(
	// 					BI::platform::keyDown(BI::PlatformKey::LEFT_SHIFT, event)
	// 				);

	// 			case kVK_End:
	// 				return g_selectedInput->onEndKey(
	// 					BI::platform::keyDown(BI::PlatformKey::LEFT_SHIFT, event)
	// 				);

	// 			default:
	// 				break;
	// 		}
	// 	}

	// 	if (BI::platform::keyDown(BI::PlatformKey::LEFT_CONTROL, event))
	// 	{
	// 		switch ([event keyCode])
	// 		{
	// 			case kVK_LeftArrow:
	// 				return g_selectedInput->onHomeKey(false);

	// 			case kVK_RightArrow:
	// 				return g_selectedInput->onEndKey(false);

	// 			default:
	// 				break;
	// 		}
	// 	}
	// }

	// key is probably a regular character, allow CCIMEDispatcher to pick up the event
	keyDownExecOIMP(self, sel, event);
}

static key_event_t keyUpExecOIMP;
void keyUpExec(EAGLView* self, SEL sel, NSEvent* event)
{
	int modifiers = (summit::keybinds::keyDown(summit::keybinds::Keys::LeftSuper, event) ? 1 : 0)
        + (summit::keybinds::keyDown(summit::keybinds::Keys::LeftShift, event) ? 2 : 0)
        + (summit::keybinds::keyDown(summit::keybinds::Keys::LeftAlt, event) ? 4 : 0)
        + (summit::keybinds::keyDown(summit::keybinds::Keys::LeftControl, event) ? 8 : 0);

    
	if (summit::keybinds::KeybindManager::get()->checkBinds(summit::keybinds::Keys::Unknown, summit::keybinds::KeyStates::Press, modifiers)) return;
	// add the other code from above herer ig?

	keyUpExecOIMP(self, sel, event);
}

// I don't plan on adding mouse stuff to summit but will maybe look into later.


// https://github.com/qimiko/click-on-steps/blob/d8a87e93b5407e5f2113a9715363a5255724c901/src/macos.mm#L101
$on_mod(Loaded)
{
	HOOK_OBJC_METHOD(EAGLView, key_event_t, keyDownExec, keyDownExec:);
	HOOK_OBJC_METHOD(EAGLView, key_event_t, keyUpExec, keyUpExec:);

	// HOOK_OBJC_METHOD(EAGLView, key_event_t, mouseDownExec, mouseDownExec:);
	// HOOK_OBJC_METHOD(EAGLView, key_event_t, mouseUpExec, mouseUpExec:);
}

#endif