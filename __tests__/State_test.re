open Jest;
open Expect;
open ReasonHooksTestingLibrary.Testing;

describe("useCounter", () => {
  open State;
  open Result;
  let container = renderHook(() => useCounter(0), ());
  test("count is 0", () =>
    expect(container->result->current.count) |> toEqual(0)
  );
  test("count is 1", () => {
    act(() => container->result->current.set(prev => prev + 1));
    expect(container->result->current.count) |> toEqual(1);
  });
  test("count is 2", () => {
    act(() => container->result->current.set(prev => prev + 1));
    expect(container->result->current.count) |> toEqual(2);
  });
});

describe("useUndo", () => {
  open State;
  open Result;
  let result = renderHook(() => useUndo(0), ())->result;
  test("(past, present, future) equals ([], 0, [])", () => {
    let current = result->current;
    expect((current.past, current.present, current.future))
    |> toEqual(([], 0, []));
  });
  test("(past, present, future) equals ([0], 1, [])", () => {
    act(() => result->current.set(prev => prev + 1));
    let current = result->current;
    expect((current.past, current.present, current.future))
    |> toEqual(([0], 1, []));
  });
  test("(past, present, future) equals ([0, 1], 2, [])", () => {
    act(() => result->current.set(prev => prev + 1));
    let current = result->current;
    expect((current.past, current.present, current.future))
    |> toEqual(([0, 1], 2, []));
  });
  test("undo: (past, present, future) equals ([0], 1, [2])", () => {
    act(() => result->current.undo());
    let current = result->current;
    expect((current.past, current.present, current.future))
    |> toEqual(([0], 1, [2]));
  });
  test("redo: (past, present, future) equals ([0,1], 2, [])", () => {
    act(() => result->current.redo());
    let current = result->current;
    expect((current.past, current.present, current.future))
    |> toEqual(([0, 1], 2, []));
  });
});

describe("useToggle", () => {
  open State;
  open Result;
  let container = renderHook(() => useToggle(false), ());
  test("on is false", () =>
    expect(container->result->current.on) |> toEqual(false)
  );
  test("on is true", () => {
    act(() => container->result->current.toggle());
    expect(container->result->current.on) |> toEqual(true);
  });
});

type store = {
  name: string,
  age: int,
};

describe("createStore", () => {
  open State;
  open Result;
  let {getState, useStore} = createStore({name: "victor", age: 21});
  let container = renderHook(() => useStore(), ());
  test("age is 21", () => {
    let current = container->result->current;
    expect((getState().age, current.state.age)) |> toEqual((21, 21));
  });
  test("age is 22", () => {
    act(() =>
      container->result->current.set(prev => {...prev, age: prev.age + 1})
    );

    expect((getState().age, container->result->current.state.age))
    |> toEqual((22, 22));
  });
});