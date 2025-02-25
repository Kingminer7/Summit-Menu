#include <Geode/platform/cplatform.h>

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
	summit::keybinds::Keys fromEvent(NSEvent* event) {
		geode::log::debug("{}", (char) ([[event characters] length] > 0
			? [[event characters] characterAtIndex:0]
			: [[event charactersIgnoringModifiers] length] > 0
				? [[event charactersIgnoringModifiers] characterAtIndex:0]
				: 0));
		switch ([event keyCode])
		{
			case kVK_Space: return Keys::Space;
			case kVK_ANSI_Quote: return Keys::Apostrophe;
			case kVK_ANSI_Comma: return Keys::Comma;
			case kVK_ANSI_Minus: return Keys::Minus;
			case kVK_ANSI_Period: return Keys::Period;
			case kVK_ANSI_Slash: return Keys::Slash;
			case kVK_ANSI_Semicolon: return Keys::Semicolon;
			case kVK_ANSI_Equal: return Keys::Equal;
			case kVK_ANSI_LeftBracket: return Keys::LeftBracket;
			case kVK_ANSI_Backslash: return Keys::Backslash;
			case kVK_ANSI_RightBracket: return Keys::RightBracket;
			case kVK_ANSI_Grave: return Keys::GraveAccent;
			// I dont think world keys exist
			// but these are where they go
			case kVK_Escape: return Keys::Escape;
			case kVK_Return: return Keys::Enter;
			case kVK_Tab: return Keys::Tab;
			case kVK_Delete: return Keys::Backspace;
			case kVK_Help: return Keys::Insert;
			case kVK_ForwardDelete: return Keys::Delete;
			case kVK_RightArrow: return Keys::Right;
			case kVK_LeftArrow: return Keys::Left;
			case kVK_DownArrow: return Keys::Down;
			case kVK_UpArrow: return Keys::Up;
			case kVK_PageUp: return Keys::PageUp;
			case kVK_PageDown: return Keys::PageDown;
			case kVK_Home: return Keys::Home;
			case kVK_End: return Keys::End;
			case kVK_CapsLock: return Keys::CapsLock;
			case NSScrollLockFunctionKey: return Keys::ScrollLock;
			// I dont think num lock exists
			// i dont know about print screen
			// or pause
			case kVK_F1: return Keys::F1;
			case kVK_F2: return Keys::F2;
			case kVK_F3: return Keys::F3;
			case kVK_F4: return Keys::F4;
			case kVK_F5: return Keys::F5;
			case kVK_F6: return Keys::F6;
			case kVK_F7: return Keys::F7;
			case kVK_F8: return Keys::F8;
			case kVK_F9: return Keys::F9;
			case kVK_F10: return Keys::F10;
			case kVK_F11: return Keys::F11;
			case kVK_F12: return Keys::F12;
			case kVK_F13: return Keys::F13;
			case kVK_F14: return Keys::F14;
			case kVK_F15: return Keys::F15;
			case kVK_F16: return Keys::F16;
			case kVK_F17: return Keys::F17;
			case kVK_F18: return Keys::F18;
			case kVK_F19: return Keys::F19;
			case kVK_F20: return Keys::F20;
			case kVK_ANSI_Keypad0: return Keys::Num0;
			case kVK_ANSI_Keypad1: return Keys::Num1;
			case kVK_ANSI_Keypad2: return Keys::Num2;
			case kVK_ANSI_Keypad3: return Keys::Num3;
			case kVK_ANSI_Keypad4: return Keys::Num4;
			case kVK_ANSI_Keypad5: return Keys::Num5;
			case kVK_ANSI_Keypad6: return Keys::Num6;
			case kVK_ANSI_Keypad7: return Keys::Num7;
			case kVK_ANSI_Keypad8: return Keys::Num8;
			case kVK_ANSI_Keypad9: return Keys::Num9;
			case kVK_ANSI_KeypadDecimal: return Keys::Decimal;
			case kVK_ANSI_KeypadDivide: return Keys::Divide;
			case kVK_ANSI_KeypadMultiply: return Keys::Multiply;
			case kVK_ANSI_KeypadMinus: return Keys::Subtract;
			case kVK_ANSI_KeypadPlus: return Keys::Add;
			case kVK_ANSI_KeypadEnter: return Keys::NumEnter;
			case kVK_ANSI_KeypadEquals: return Keys::NumEqual;
			case kVK_Shift: return Keys::LeftShift;
			case kVK_Control: return Keys::LeftControl;
			case kVK_Option: return Keys::LeftAlt;
			case kVK_Command: return Keys::LeftSuper;
			case kVK_RightShift: return Keys::RightShift;
			case kVK_RightControl: return Keys::RightControl;
			case kVK_RightOption: return Keys::RightAlt;
			case kVK_RightCommand: return Keys::RightSuper;
			// no idea about menu key, what even is that lmao
			default: break;
		}

				// https://github.com/WebKit/WebKit/blob/5c8281f146cfbf4b6189b435b80c527f138b829f/Source/WebCore/platform/mac/PlatformEventFactoryMac.mm#L559
		// we use this instead of [event keyCode] because the returned value of keyCode for letters is keyboard locale-specific
		int code = [[event characters] length] > 0
			? [[event characters] characterAtIndex:0]
			: [[event charactersIgnoringModifiers] length] > 0
				? [[event charactersIgnoringModifiers] characterAtIndex:0]
				: 0;

		switch (code)
		{
			case 'a': case 'A':
				return Keys::A;
			case 'b': case 'B':
				return Keys::B;
			case 'c': case 'C':
				return Keys::C;
			case 'd': case 'D':
				return Keys::D;
			case 'e': case 'E':
				return Keys::E;
			case 'f': case 'F':
				return Keys::F;
			case 'g': case 'G':
				return Keys::G;
			case 'h': case 'H':
				return Keys::H;
			case 'i': case 'I':
				return Keys::I;
			case 'j': case 'J':
				return Keys::J;
			case 'k': case 'K':
				return Keys::K;
			case 'l': case 'L':
				return Keys::L;
			case 'm': case 'M':
				return Keys::M;
			case 'n': case 'N':
				return Keys::N;
			case 'o': case 'O':
				return Keys::O;
			case 'p': case 'P':
				return Keys::P;
			case 'q': case 'Q':
				return Keys::Q;
			case 'r': case 'R':
				return Keys::R;
			case 's': case 'S':
				return Keys::S;
			case 't': case 'T':
				return Keys::T;
			case 'u': case 'U':
				return Keys::U;
			case 'v': case 'V':
				return Keys::V;
			case 'w': case 'W':
				return Keys::W;
			case 'x': case 'X':
				return Keys::X;
			case 'y': case 'Y':
				return Keys::Y;
			case 'z': case 'Z':
				return Keys::Z;
			case '0': return Keys::Num0;
			case '1': return Keys::Num1;
			case '2': return Keys::Num2;
			case '3': return Keys::Num3;
			case '4': return Keys::Num4;
			case '5': return Keys::Num5;
			case '6': return Keys::Num6;
			case '7': return Keys::Num7;
			case '8': return Keys::Num8;
			case '9': return Keys::Num9;
			default:
				break;
		}

		return Keys::Unknown;
	};

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

		if (summit::keybinds::KeybindManager::get()->checkBinds(summit::keybinds::fromEvent(event), [event isARepeat] ? summit::keybinds::KeyStates::Hold : summit::keybinds::KeyStates::Press, modifiers)) return;
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

    
	if (summit::keybinds::KeybindManager::get()->checkBinds(summit::keybinds::fromEvent(event), summit::keybinds::KeyStates::Release, modifiers)) return;

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