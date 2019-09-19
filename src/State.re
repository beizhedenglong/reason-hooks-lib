type counterType = {
  counter: int,
  set: (int => int) => unit,
  reset: unit => unit,
  inc: unit => unit,
  dec: unit => unit,
};
let useCounter = initial => {
  let (counter, set) = React.useState(() => initial);
  {
    counter,
    set,
    reset: () => set(_ => initial),
    inc: () => set(prev => prev + 1),
    dec: () => set(prev => prev - 1),
  };
};

type undoDataType('a) = {
  past: list('a),
  present: 'a,
  future: list('a),
};

type undoType('a) = {
  undo: unit => unit,
  redo: unit => unit,
  set: ('a => 'a) => unit,
  past: list('a),
  present: 'a,
  future: list('a),
};

let useUndo = initial => {
  let initialData = {past: [], present: initial, future: []};
  let (state, setState) = React.useState(() => initialData);
  let undo = () =>
    setState(prevState =>
      switch (List.rev(prevState.past)) {
      | [] => prevState
      | [previous, ...rest] => {
          past: List.rev(rest),
          present: previous,
          future: [prevState.present, ...prevState.future],
        }
      }
    );

  let set = f =>
    setState(({past, present}) =>
      {past: past @ [present], present: f(present), future: []}
    );
  let redo = () =>
    setState(prevState =>
      switch (prevState.future) {
      | [] => prevState
      | [next, ...rest] => {
          past: prevState.past @ [prevState.present],
          present: next,
          future: rest,
        }
      }
    );
  {
    past: state.past,
    present: state.present,
    future: state.future,
    set,
    undo,
    redo,
  };
};

type toggleType = {
  on: bool,
  reset: unit => unit,
  toggle: unit => unit,
  set: (bool => bool) => unit,
};
let useToggle = initial => {
  let (on, set) = React.useState(() => initial);
  {on, reset: () => set(_ => initial), toggle: () => set(prev => !prev), set};
};

type stateType('a) = {
  state: 'a,
  set: ('a => 'a) => unit,
};
type globalStoreType('a) = {
  useGlobalStore: unit => stateType('a),
  getState: unit => 'a,
};

let createGlobalStore = initial => {
  let state = ref(initial);
  let listeners = ref([]);
  let setState = updater => {
    state := updater(state^);
    List.iter(f => f(_ => state^), listeners^);
  };
  let useGlobalStore = () => {
    let (localState, set) = React.useState(() => state^);
    React.useEffect1(
      () => {
        listeners := [set, ...listeners^];
        Some(() => listeners := List.filter(f => f !== set, listeners^));
      },
      [||],
    );
    {state: localState, set: setState};
  };
  {useGlobalStore, getState: () => state^};
};

let useStateCallback = (initial, f) => {
  open Lifecycle;
  let (state, set) = React.useState(() => initial);
  useDidUpdate(f, [|state|]);
  {state, set};
};