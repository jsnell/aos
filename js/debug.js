function myHandleException(e)
{
	var p = output.appendChild(document.createElement('pre'));
	for (var prop in e) {
		try {
			if (typeof e[prop] == "function")
				continue;
			p.appendChild(document.createTextNode(prop + ': ' +
			    e[prop]));
			p.appendChild(document.createElement('br'));
		} catch (e) {
			/* do nothing */
		}
	}
}

function myStack(frames)
{
	var caller, depth;
	var stack = new Array();
	var f = frames;
	for (caller = arguments.callee, depth = 0;
	    caller && depth < 12;
	    caller = caller.caller, depth++) {
		if (f) {
			f--;
			continue;
		}
		var args = new Array();
		for (var i = 0; i < caller.arguments.length; i++)
			args.push(caller.arguments[i]); 
		stack.push({
		    caller: caller,
		    args: args
		});
	}
	this.stack = stack;
	try {
		x.y = 4;
	} catch (e) {
		if (e.stack) {
			var str = e.stack.toString();
			f = frames;
			while (f) {
				f--;
				str = str.substring(str.indexOf('\n') + 1);
			}
			this.nativeStack = str;
		}
	}
}

myStack.prototype.toString = function ()
{
	var ret = 'Computed Stack:\n';

	for (var i = 0; i < this.stack.length; i++) {
		var frame = this.stack[i];

		ret += getFunctionName(frame.caller);
		ret += '(';

		for (var j = 0; j < frame.args.length; j++) {
			if (j !== 0)
				ret += ', ';
			switch (typeof frame.args[j]) {
			case 'string':
				ret += '"' + frame.args[j] + '"';
				break;

			case 'function':
				ret += '<function>';
				break;

			default:
				ret += frame.args[j];
			}
		}

		ret += ')\n';
	}

	if (this.nativeStack) {
		ret += '\nNative Stack:\n';
		ret += this.nativeStack;
	}

	return (ret);
}

function getFunctionName(f)
{
	for (var name in window) {
		try {
			if (window[name] == f)
				return (name);
		} catch (e) {

		}
	}

	return ("<anonymous>");
}

function mySetTimeout(callback, timeout)
{
	var wrapper = function () {
		try {
			callback();
		} catch (e) {
			myHandleException(e);
		}
	};

	return (setTimeout(wrapper, timeout));
}

function myAddEventListener(obj, event, callback, capture)
{
	var wrapper = function (evt) {
		try {
			callback(evt);
		} catch (e) {
			myHandleException(e);
		}
	};
	if (!obj.listeners)
		obj.listeners = new Array();
	obj.listeners.push({
		event: event,
		wrapper: wrapper,
		capture: capture,
		callback: callback
	});
	obj.addEventListener(event, wrapper, capture);
}

function myRemoveEventListener(obj, event, callback, capture)
{
	for (var i = 0; i < obj.listeners.length; i++) {
		if (obj.listeners[i].event == event &&
		    obj.listeners[i].callback == callback &&
		    obj.listeners[i].capture == capture)
			break;
	}

	if (i == obj.listeners.length)
		throw (new Error('failed to find event listener'));

	obj.removeListener(event, obj.listeners[i].wrapper, capture);
	obj.listeners.splice(i, 1);
}
