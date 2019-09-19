open Jest;
open Expect;
open ReasonHooksTestingLibrary.Testing;

describe("useDidMount", () => {
  open Lifecycle;
  open State;
  open Result;
  let useDidMountTest = () => {
    let {counter, inc} = useCounter(0);
    useDidMount(() => {
      inc();
      None;
    });
    counter;
  };
  let container = renderHook(() => useDidMountTest(), ());
  test("counter is 0", () =>
    expect(container->result->current) |> toBe(1)
  );
});