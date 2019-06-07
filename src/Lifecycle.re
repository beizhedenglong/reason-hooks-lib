let useDidMount = f => React.useEffect1(f, [||]);

let useWillUnmount = f => React.useEffect1(() => Some(() => f()), [||]);

let useDidUpdate = (f, conditions) => {
  let didMoutRef = React.useRef(false);
  React.useEffect1(
    () =>
      React.Ref.(
        switch (didMoutRef->current) {
        | false =>
          didMoutRef->setCurrent(true);
          None;
        | true => f()
        }
      ),
    conditions,
  );
};